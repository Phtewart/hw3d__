
cbuffer PointLightCBuf
{
    float3 viewLightPos;
    float3 ambient;
    float3 PointLightColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

float3 MapNormal(
    const in float3 tan,
    const in float3 bitan,
    const in float3 normal,
    const in float2 tc,
    uniform Texture2D nmap,
    uniform SamplerState splr)
{
    // build the tranform (rotation) into same space as tan/bitan/normal (target space)
    float3 N = normal;
    float3 T = normalize(tan - dot(tan, N) * N);
    float3 B = cross(N, T);
    
    const float3x3 tanToTarget = float3x3(T, B, N);
    // sample and unpack the normal from texture into target space   
    float3 normalSample = nmap.Sample(splr, tc).xyz;
    normalSample.y = 1 - normalSample.y;
    //normalSample = normalSample * float3(1.0f, -1.0f, 1.0f);
    const float3 tanNormal = normalSample * 2.0f - 1.0f;
    // bring normal from tanspace into target space
    return normalize(mul(tanNormal, tanToTarget));
}

float Attenuate(uniform float attConst, uniform float attLin, uniform float attQuad, const in float distFragToL)
{
    return 1.0f / (attConst + attLin * distFragToL + attQuad * (distFragToL * distFragToL));
}

float3 PointLightDiffuse(
    uniform float3 diffuseColor,
    uniform float diffuseIntensity,
    const in float att,
    const in float3 viewDirFragToL,
    const in float3 viewNormal)
{
    return diffuseColor * diffuseIntensity * att * max(0.0f, dot(viewDirFragToL, viewNormal));
}

float3 PointLightSpecular(
    const in float3 specularColor,
    uniform float specularIntensity,
    const in float3 viewNormal,
    const in float3 viewFragToL,
    const in float3 viewPos,
    const in float att,
    const in float specularPower)
{
    // calculate reflected light vector
    const float3 w = viewNormal * dot(viewFragToL, viewNormal);
    const float3 r = normalize(w * 2.0f - viewFragToL);
    // vector from camera to fragment (in view space)
    const float3 viewCamToFrag = normalize(viewPos);
    // calculate specular component color based on angle between
    // viewing vector and reflection vector, narrow with power function
    return att * specularColor * specularIntensity * pow(max(0.0f, dot(-r, viewCamToFrag)), specularPower);
}

struct LightVectorData
{
    float3 vToL;
    float3 dirToL;
    float distToL;
};

LightVectorData CalculateLightVectorData(const in float3 lightPos, const in float3 fragPos)
{
    LightVectorData lv;
    lv.vToL = lightPos - fragPos;
    lv.distToL = length(lv.vToL);
    lv.dirToL = lv.vToL / lv.distToL;
    return lv;
}

cbuffer ObjectCBuf
{
    bool normalMapEnabled;
    bool specularMapEnabled;
    bool hasGloss;
    float specularPowerConst;
    float3 specularColor;
    float specularMapWeight;
};

struct PS_INPUT
{
    float3 viewFragPos : Position;
    float3 viewNormal : Normal;
    float3 viewTan : Tangent;
    float3 viewBitan : Bitangent;
    float2 tc : Texcoord;
};

Texture2D tex;
Texture2D spec;
Texture2D nmap;

SamplerState splr;

float4 main(PS_INPUT psInput) : SV_Target
{
    // normalize the mesh normal
    psInput.viewNormal = normalize(psInput.viewNormal);
    // replace normal with mapped if normal mapping enabled
    if (normalMapEnabled)
    {
        psInput.viewNormal = MapNormal(normalize(psInput.viewTan), normalize(psInput.viewBitan), psInput.viewNormal, psInput.tc, nmap, splr);
    }
	// fragment to light vector data
    const LightVectorData lv = CalculateLightVectorData(viewLightPos, psInput.viewFragPos);
    // specular parameter determination (mapped or uniform)
    float3 specularReflectionColor;
    float specularPower = specularPowerConst;
    if (specularMapEnabled)
    {
        const float specularSample = spec.Sample(splr, psInput.tc).r;
        specularReflectionColor = PointLightColor * specularMapWeight * specularSample;
        if (hasGloss)
        {
            specularPower = pow(2.0f, specularSample * 7.0f);
        }
    }
    else
    {
        specularReflectionColor = specularColor;
    }
	// attenuation
    const float att = Attenuate(attConst, attLin, attQuad, lv.distToL);
	// diffuse light
    const float3 diffuse = PointLightDiffuse(PointLightColor, diffuseIntensity, att, lv.dirToL, psInput.viewNormal);
    // specular reflected
    const float3 specularReflected = PointLightSpecular(
        specularReflectionColor, 1.0f, psInput.viewNormal,
        lv.vToL, psInput.viewFragPos, att, specularPower
    );
	// final color = attenuate diffuse & ambient by diffuse texture color and add specular reflected
    return float4(saturate((diffuse + ambient) * tex.Sample(splr, psInput.tc).rgb + specularReflected), 1.0f);
}
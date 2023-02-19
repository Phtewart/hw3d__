cbuffer LightCBuf
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

cbuffer ObjectCBuf
{
    float3 materialColor;
    float specularIntensity;
    float specularPower;
};

struct PS_IN
{
    float3 worldPos : Position;
    float3 n : Normal;
};

float4 main(PS_IN IN) : SV_Target
{
	// fragment to light vector data
    const float3 vToL = lightPos - IN.worldPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;
	// attenuation
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
	// diffuse intensity
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, IN.n));
	// reflected light vector
    const float3 w = IN.n * dot(vToL, IN.n);
    const float3 r = w * 2.0f - vToL;
	// calculate specular intensity based on angle between viewing vector and reflection vector, narrow with power function
    const float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f, dot(normalize(-r), normalize(IN.worldPos))), specularPower);
	// final color
    return float4(saturate((diffuse + ambient + specular) * materialColor), 1.0f);
}
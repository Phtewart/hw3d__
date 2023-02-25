cbuffer CBuf
{
    matrix modelView;
    matrix modelViewProj;
};

struct VS_IN
{
    float3 pos : Position;
    float3 n : Normal;
    float3 tan : Tangent;
    float3 bitan : Bitangent;
    float2 tc : Texcoord;
};
struct VSOut
{
    float3 worldPos : Position;
    float3 normal : Normal;
    float3 tan : Tangent;
    float3 bitan : Bitangent;
    float2 tc : Texcoord;
    float4 pos : SV_Position;
};

VSOut main(VS_IN IN)
{
    VSOut vso;
    vso.worldPos = (float3) mul(float4(IN.pos, 1.0f), modelView);
    vso.normal = mul(IN.n, (float3x3) modelView);
    vso.tan = mul(IN.tan, (float3x3) modelView);
    vso.bitan = mul(IN.bitan, (float3x3) modelView);
    vso.pos = mul(float4(IN.pos, 1.0f), modelViewProj);
    vso.tc = IN.tc;
    return vso;
}
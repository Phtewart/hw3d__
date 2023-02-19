cbuffer CBuf
{
    matrix modelView;
    matrix modelViewProj;
};

struct VS_IN
{
    float3 pos : Position;
    float3 n : Normal;
};
struct VSOut
{
    float3 worldPos : Position;
    float3 normal : Normal;
    float4 pos : SV_Position;
};

VSOut main(VS_IN IN)
{
    VSOut vso;
    vso.worldPos = (float3) mul(float4(IN.pos, 1.0f), modelView);
    vso.normal = mul(IN.n, (float3x3) modelView);
    vso.pos = mul(float4(IN.pos, 1.0f), modelViewProj);
    return vso;
}
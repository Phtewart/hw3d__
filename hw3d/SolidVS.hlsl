struct VS_IN
{
    float3 pos : Position;
};

cbuffer CBuf
{
    matrix model;
    matrix modelViewProj;
};

float4 main(VS_IN IN) : SV_Position
{
    return mul(float4(IN.pos, 1.0f), modelViewProj);
}

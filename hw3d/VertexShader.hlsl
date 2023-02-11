struct VSOut
{
    float3 color : Color;
    float4 pos : SV_Position;
};
cbuffer cBuf
{
    matrix transform;
};

VSOut main(float2 pos : Position, float3 color : Color)
{
    VSOut vso;
    vso.color = color;
    vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f),transform);
    
    return vso;
}
cbuffer cBuf
{
    float4 face_color[6];
};
float4 main(uint tID : SV_PrimitiveID) : SV_Target
{
    return face_color[tID/2];
}
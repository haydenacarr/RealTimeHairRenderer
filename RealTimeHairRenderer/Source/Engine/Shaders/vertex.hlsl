struct VSInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

PSInput VSMain(VSInput input)
{
    PSInput output;
    output.pos = float4(input.pos, 1.0f);
    output.color = input.color;
    return output;
}
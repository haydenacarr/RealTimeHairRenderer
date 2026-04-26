struct VSInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 worldPos : TEXCOORD0;
    float3 normal : NORMAL;
};

cbuffer MvpCB : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
    float4 lightDir;
    float4 cameraPos;
};

PSInput VSMain(VSInput input)
{
    PSInput output;
    
    float4 worldPos = mul(float4(input.position, 1.0f), model);
    float4 viewPos = mul(worldPos, view);
    
    output.pos = mul(viewPos, projection);
    output.worldPos = worldPos.xyz;
    output.normal = mul(input.normal, (float3x3) model);
    
    return output;
}
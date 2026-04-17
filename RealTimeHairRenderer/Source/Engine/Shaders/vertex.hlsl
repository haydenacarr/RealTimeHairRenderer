struct VSInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float3 tangent : TANGENT;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 worldPos : TEXCOORD0;
    float4 color : COLOR;
    float3 tangent : TANGENT;
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
    
    float4 worldPosition = mul(float4(input.pos, 1.0f), model);
    output.worldPos = worldPosition.xyz;

    float4 viewPos = mul(worldPosition, view);
    output.pos = mul(viewPos, projection);
    
    output.color = input.color;
    output.tangent = normalize(mul(input.tangent, (float3x3) model));
    
    return output;
}
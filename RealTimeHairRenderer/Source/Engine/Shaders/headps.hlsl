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

float4 PSMain(PSInput input) : SV_TARGET
{
    float3 N = normalize(input.normal);
    float3 L = normalize(lightDir.xyz);
    
    // Basic Lambertian diffuse
    float diffuse = max(0.0, dot(N, L));
   
    float3 ambient = 0.15f;
    float3 headColor = float3(0.7, 0.6, 0.55);
    float3 finalColor = headColor * (diffuse + ambient);
    
    return float4(finalColor, 1.0f);
}
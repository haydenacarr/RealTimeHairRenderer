struct PSInput
{
    float4 pos : SV_POSITION;
    float3 worldPos : TEXCOORD0;
    float4 color : COLOR;
    float3 tangent : TANGENT;
    uint primID : SV_PrimitiveID;
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
    float Kd = 0.7; 
    float Ks1 = 0.5;
    float Ks2 = 0.4; 
    float p1 = 80.0; 
    float p2 = 25.0; 
    float3 random = frac(sin(input.primID * 12.9898) * 43758.5453);
    float3 variation = 0.8 + (random * 0.3);
    float3 colour = input.color.rgb * variation;
    
    float3 T = normalize(input.tangent);
    float3 L = normalize(lightDir.xyz);
    float3 E = normalize(cameraPos.xyz - input.worldPos);

    // Kajiya-Kay Diffuse calculation
    float cosTL = dot(T, L);
    float sinTL = sqrt(max(0.0, 1.0 - cosTL * cosTL));
    float diffuse = Kd * sinTL;
    
    // Marschner 
    float3 N = normalize(input.worldPos);
    float3 T1 = normalize(T + N * 0.1);
    float3 T2 = normalize(T - N * 0.15); 
    
    // Primary specular
    float cosTL1 = dot(T1, L);
    float sinTL1 = sqrt(max(0.0, 1.0 - cosTL1 * cosTL1));
    float cosTE1 = dot(T1, E);
    float sinTE1 = sqrt(max(0.0, 1.0 - cosTE1 * cosTE1));
    float specPrimary = Ks1 * pow(max(0.0, cosTL1 * cosTE1 + sinTL1 * sinTE1), p1);
    
    // Secondary specular
    float cosTL2 = dot(T2, L);
    float sinTL2 = sqrt(max(0.0, 1.0 - cosTL2 * cosTL2));
    float cosTE2 = dot(T2, E);
    float sinTE2 = sqrt(max(0.0, 1.0 - cosTE2 * cosTE2));
    float3 specSecondary = Ks2 * pow(max(0.0, cosTL2 * cosTE2 + sinTL2 * sinTE2), p2);
    specSecondary = specSecondary * random;
    
    // Shadows were too harsh so ambient light was added
    float ambient = 0.1;

    float3 output = colour * (diffuse + ambient) + specPrimary + specSecondary;
    
    return float4(output, input.color.a);
}
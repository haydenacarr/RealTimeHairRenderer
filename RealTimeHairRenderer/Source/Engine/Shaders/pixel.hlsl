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

float4 PSMain(PSInput input) : SV_TARGET
{
    float Kd = 0.8; 
    float Ks = 0.2;
    float p = 20.0;
    
    float3 T = normalize(input.tangent);
    float3 L = normalize(lightDir.xyz);
    float3 E = normalize(cameraPos.xyz - input.worldPos);

    // Kajiya-Kay Diffuse calculation
    float cosTL = dot(T, L);
    float sinTL = sqrt(max(0.0, 1.0 - cosTL * cosTL));
    float diffuse = Kd * sinTL;

    float cosTE = dot(T, E);
    float sinTE = sqrt(max(0.0, 1.0 - cosTE * cosTE));
    float specular = Ks * pow(max(0.0, cosTL * cosTE + sinTL * sinTE), p);
    
    // Shadows were too harsh so ambient light was added
    float ambient = 0.1;

    float3 output = input.color.rgb * (diffuse + ambient) + specular;
    
    return float4(output, input.color.a);
}
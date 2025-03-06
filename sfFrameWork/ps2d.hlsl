#include "Constant.hlsli"
Texture2D diffuseTexture : register(t0);
SamplerState mySampler : register(s0); //ƒTƒ“ƒvƒ‰[
struct In
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

PS2D_Out main(In input)
{
    PS2D_Out output;
    
    output.baseColor = input.color;
    
    if(textureEnable.x)
    {
        output.baseColor *= diffuseTexture.Sample(mySampler, input.uv);
    }
    
    float alpha = output.baseColor.a;
    output.alphaBuffer = float4(alpha, alpha, alpha, 1);
    
    return output;
}
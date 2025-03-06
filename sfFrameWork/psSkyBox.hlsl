SamplerState mySampler : register(s0); //�T���v���[
Texture2D skyBoxTexture : register(t0); //�X�J�C�{�b�N�X�e�N�X�`��
struct In
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 main(In input) : SV_TARGET
{
    float4 color = skyBoxTexture.Sample(mySampler, input.uv);
    
    return color;
}
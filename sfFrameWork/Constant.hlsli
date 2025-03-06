struct PS3D_In
{
    float4 pos : SV_POSITION; //�X�N���[�����W
    float4 wpos : POSITION; //���[���h���W
    float2 uv : TEXCOORD; //UV���W
    float3 normal : NORMAL; //�@��
    float4 color : COLOR; //���_�J���[
    float4 shadowSpacePos : LIGHTPOS; //�e�p���C�g���猩���X�N���[�����W
};

struct PS3D_Out
{
    float4 baseColor : SV_Target0;  //�x�[�X�J���[
    float4 normalColor : SV_Target1;//�@���J���[
    float4 alpha : SV_Target2;      //�A���t�@�[�x
    float4 luminance : SV_Target3;  //�P�x
};

struct PS2D_Out
{
    float4 baseColor : SV_Target0;
    float4 alphaBuffer : SV_Target1;
};

#if 1   //�Œ背�W�X�^(���R���W�X�^��6����)
cbuffer World : register(b0)
{
    matrix worldMatrix;
    matrix rotMtx;
}

cbuffer Camera : register(b1)
{
    float4 cameraPos;
    matrix view;
    matrix proj;
    matrix shadowViewProj;
}

cbuffer Material : register(b2)
{
    float4 diffuseColor;
    float4 emissionColor;
    float4 textureEnable;
}

cbuffer MotionBuffer : register(b3)
{
    matrix motions[400];
}

cbuffer Line : register(b4)
{
    float4 p1;
    float4 p2;
    float4 color;
}

cbuffer System : register(b5)
{
    float time;
    float2 screenSize;
}

#endif
#pragma once
#include "Singleton.h"
#include "MainDevice.h"
#include "OnScreenRTV.h"
#include "OffScreenRTV.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "Depth.h"
#include "BlendState.h"

#include "RenderingBuffer2D.h"
#include "RenderingBuffer3D.h"
#include "ConstBuffer.h"

#include "Debug.h"

struct WorldMatrixBuffer
{
	DirectX::XMMATRIX mtx;
	DirectX::XMMATRIX rot;
};

struct VP
{
	DirectX::XMFLOAT4 cameraPos;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
	DirectX::XMMATRIX shadowVP;
};

struct mtl
{
	DirectX::XMFLOAT4 diffuseColor;
	DirectX::XMFLOAT4 emissionColor;
	DirectX::XMFLOAT4 textureEnable;
};

struct cmotion
{
	DirectX::XMMATRIX matrix[400];
};

struct System
{
	DirectX::XMFLOAT4 time;
	DirectX::XMFLOAT2A screenSize;
};

namespace sf
{
	namespace dx
	{
		//DirectX�N���X(D3D/�V���O���g��)
		class DirectX11 :public Singleton<DirectX11>
		{
		public:
			/// <summary>
			/// DirectX11�̏�����
			/// </summary>
			/// <param name="hwnd">�E�B���h�E�n���h��</param>
			void Create(HWND hwnd);

			void Flip() { mainDevice.Flip(); }

			/// <summary>
			/// ���C���f�o�C�X�̎擾
			/// </summary>
			/// <returns></returns>
			MainDevice& GetMainDevice(){ return mainDevice; }

			/// <summary>
			/// ���̃����_�����O�o�b�t�@��p�ӂ���
			/// </summary>
			void SetNextRenderingDoubleBuffer3D();

			/// <summary>
			/// �X�J�C�{�b�N�X�`��J�n�ݒ�
			/// </summary>
			void SetRenderingDoubleBuffer3DSkyBox();

			/// <summary>
			/// 3D�`��J�n�ݒ�
			/// </summary>
			void SetRenderingDoubleBuffer3D();

			/// <summary>
			/// 2D�`��J�n�ݒ�
			/// </summary>
			void SetRenderingDoubleBuffer2D();

			/// <summary>
			/// �I���X�N���[�������_�����O
			/// </summary>
			void OnScreenRendering();

			/// <summary>
			/// �r���[�|�[�g�̐ݒ�
			/// </summary>
			void SetViewPort();
			void SetViewPort(int w, int h);

		private:
			void LoadShader();

			void PostProcessing();
			void DownSamplingX();
			void DownSamplingY();

		public:
			//�萔�o�b�t�@
			ConstBuffer<WorldMatrixBuffer> wBuffer;
			ConstBuffer<VP> vpBuffer;
			ConstBuffer<mtl> mtlBuffer;
			ConstBuffer<cmotion> motionBuffer;
			ConstBuffer<debug::Debug::LineData> lineBuffer;
			ConstBuffer<System> systemBuffer;

			//�V�F�[�_�[
			shader::VertexShader vs3d;
			shader::VertexShader vsMotion;
			shader::VertexShader vsNone;

			shader::GeometryShader gsNone;
			shader::GeometryShader gsCube;
			shader::GeometryShader gs2d;
			shader::GeometryShader gsOnScreen;
			shader::GeometryShader gsDebugLine;
			shader::GeometryShader gsDownX;
			shader::GeometryShader gsDownY;

			shader::PixelShader ps3d;
			shader::PixelShader ps2d;
			shader::PixelShader psOnScreen;
			shader::PixelShader psDebugLine;
			shader::PixelShader psShadow;
			shader::PixelShader psBlur;
			shader::PixelShader psPostProcess;


		public:
			//���C���f�o�C�X
			MainDevice mainDevice;

			//�I���X�N���[��
			OnScreenRTV onScreen;

			//�����_�����O�o�b�t�@
			rbuffer::RenderingBuffer2D rb2d;
			rbuffer::RenderingDoubleBuffer3D rb3d;
			OffScreenRTV shadowRTV;

			OffScreenRTV downX;
			OffScreenRTV downY;

			//�[�x
			Depth depth;

			//�f�B�t�@�[�h�R���e�L�X�g
			Context context;

			//�T���v���[
			Sampler sampler;

			BlendState alphaBlend;
			BlendState addBlend;

			//�E�B���h�E�n���h��
			HWND hwnd;
		};
	}
}

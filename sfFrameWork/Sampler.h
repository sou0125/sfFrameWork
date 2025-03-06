#pragma once
#include "D3D.h"
namespace sf
{
	namespace dx
	{
		//�T���v���[(D3D)
		class Sampler:public D3D
		{
		public:
			~Sampler();

			void Release()override;

			/*
			---�T���v���[�̃p�����[�^���---

			�ZD3D11_TEXTURE_ADDRESS_WRAP:
			�e�N�X�`������UV���W�Ɍ��炸���݂��A���]���J��Ԃ�

			�ZD3D11_TEXTURE_ADDRESS_MIRROR:
			�e�N�X�`������UV���W�Ɍ��炸���݂��A���],���]���J��Ԃ�

			�ZD3D11_TEXTURE_ADDRESS_CLAMP:
			�e�N�X�`������UV���W0.0f�`1.0f�̂ݑ��݂���

			�ZD3D11_TEXTURE_ADDRESS_BORDER:
			UV���W0.0f�`1.0f�͈̔͂̂݃N���b�s���O�����B���̑��̗̈�͕`�悳��Ȃ�

			�ZD3D11_TEXTURE_ADDRESS_MIRROR_ONCE:
			�e�N�X�`������UV���W-1.0f�`1.0f�ɑ��݂��A���],���]���đ��݂���
			*/
			HRESULT Create(D3D11_TEXTURE_ADDRESS_MODE u = D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_MODE v = D3D11_TEXTURE_ADDRESS_WRAP);

			void SetGPU(ID3D11DeviceContext* d3dContext)const;

		private:
			ID3D11SamplerState* d3dSampler = nullptr;
		};
	}
}
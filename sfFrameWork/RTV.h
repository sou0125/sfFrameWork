#pragma once
#include "D3D.h"

namespace sf
{
	namespace dx
	{
		//�����_�[�^�[�Q�b�g�N���X(D3D)
		class RTV :public D3D
		{
		public:
			virtual ~RTV();

			void Release()override;

		public:
			ID3D11RenderTargetView* GetRTV()const { return rtv; }

		protected:
			ID3D11RenderTargetView* rtv = nullptr;
		};
	}
}
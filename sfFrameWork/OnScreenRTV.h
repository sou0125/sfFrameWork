#pragma once
#include "RTV.h"

namespace sf
{
	namespace dx
	{
		//�I���X�N���[�������_�[�^�[�Q�b�g�N���X(D3D)
		class OnScreenRTV :public RTV
		{
		public:
			HRESULT Create();
		};
	}
}

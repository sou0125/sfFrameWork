#pragma once
#include "OffScreenRTV.h"

#define BUFFERSIZE	(4)

namespace sf
{
	namespace rbuffer
	{
		//�����_�����O�o�b�t�@���N���X
		class RenderingBuffer
		{
		public:
			virtual ~RenderingBuffer() {}

			//RBuffer�̓h��Ԃ�
			virtual void ClearBuffer(ID3D11DeviceContext* d3dContext) = 0;

			//RBuffer�̃Z�b�g
			virtual void SetRBuffer(ID3D11DeviceContext* d3dContext, ID3D11DepthStencilView* depth) = 0;

		public:
			const dx::OffScreenRTV& GetBaseColorRTV()const { return baseColorRTV; }
			const dx::OffScreenRTV& GetLuminanceRTV()const { return luminanceRTV; }
			const dx::OffScreenRTV& GetAlphaRTV()const { return alphaRTV; }

		protected:
			//��{�F
			dx::OffScreenRTV baseColorRTV;

			//�P�x���o
			dx::OffScreenRTV luminanceRTV;

			//�������_�[�^�[�Q�b�g
			dx::OffScreenRTV alphaRTV;
		};
	}
}
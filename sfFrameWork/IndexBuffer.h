#pragma once
#include <vector>
#include "D3D.h"

namespace sf
{
	namespace dx
	{
		//�C���f�b�N�X�o�b�t�@(D3D)
		class IndexBuffer :public D3D
		{
		public:
			~IndexBuffer();

			void Release()override;

			HRESULT Create(const std::vector<WORD>& indcies);

			void SetGPU(ID3D11DeviceContext* d3dContext)const;

			int GetIndexSize()const { return iSize; }

		private:
			ID3D11Buffer* buffer = nullptr;

			int iSize = 0;
		};
	}
}
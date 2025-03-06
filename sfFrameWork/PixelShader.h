#pragma once
#include "Shader.h"

namespace sf
{
	namespace dx
	{
		namespace shader
		{
			//�s�N�Z���V�F�[�_(D3D)
			class PixelShader :public Shader
			{
			public:
				~PixelShader();

				void Release()override;

				HRESULT Make(void* pData, UINT size)override;

				void SetGPU(ID3D11DeviceContext* d3dContext)override;

				static void Lock();
				static void UnLock();

			private:
				ID3D11PixelShader* s = nullptr;

				static bool lock;
			};
		}
	}
}
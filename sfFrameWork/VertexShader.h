#pragma once
#include "Shader.h"

namespace sf
{
	namespace dx
	{
		namespace shader
		{
			//���_�V�F�[�_(D3D)
			class VertexShader :public Shader
			{
			public:
				~VertexShader();

				void Release()override;

				HRESULT Make(void* pData, UINT size)override;

				void SetGPU(ID3D11DeviceContext* d3dContext)override;

			private:
				HRESULT MakeInputLayout(void* pData, UINT size);

			private:
				ID3D11VertexShader* s = nullptr;

				ID3D11InputLayout* inputLayout = nullptr;
			};
		}
	}
}
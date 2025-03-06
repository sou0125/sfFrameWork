#pragma once
#include "D3D.h"

namespace sf
{
	namespace dx
	{
		//�f�o�C�X�R���e�L�X�g(D3D)
		class Context :public D3D
		{
		public:
			virtual ~Context();

			void Release()override;

			/// <summary>
			/// �R���e�L�X�g�̃Z�b�g
			/// </summary>
			/// <param name="v"></param>
			void SetContext(ID3D11DeviceContext* v);

			/// <summary>
			/// �����_�[�^�[�Q�b�g�̓h��Ԃ�
			/// </summary>
			/// <param name="rtv"></param>
			void ClearRTV(ID3D11RenderTargetView* rtv);
			void ClearRTV(ID3D11RenderTargetView* rtv, const FLOAT color[4]);

			ID3D11DeviceContext* GetContext()const { return d3dContext; }

			void operator=(ID3D11DeviceContext* v);

		protected:
			ID3D11DeviceContext* d3dContext = nullptr;
		};
	}
}

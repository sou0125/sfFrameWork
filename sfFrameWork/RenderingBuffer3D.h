#pragma once
#include "RenderingBuffer.h"
namespace sf
{
	namespace rbuffer
	{
		//3D�p�����_�����O�o�b�t�@
		class RenderingBuffer3D :public RenderingBuffer
		{
		public:
			HRESULT Create(int w, int h);

			void ClearBuffer(ID3D11DeviceContext* d3dContext)override;
			void SetRBuffer(ID3D11DeviceContext* d3dContext, ID3D11DepthStencilView* depth)override;


			const dx::OffScreenRTV& GetNormalRTV()const { return normalRTV; }

		private:
			//�@��
			dx::OffScreenRTV normalRTV;
		};


		//3D�p�����_�����O�_�u���o�b�t�@�o�b�t�@
		class RenderingDoubleBuffer3D
		{
		public:
			HRESULT Create(int w, int h);

			void NextBuffer();

			void ClearBuffer(ID3D11DeviceContext* d3dContext);
			void SetRBuffer(ID3D11DeviceContext* d3dContext, ID3D11DepthStencilView* depth);

			/// <summary>
			/// ���݂̃����_�����O�o�b�t�@���擾
			/// </summary>
			/// <returns></returns>
			RenderingBuffer3D& Get() { return buffers[idx]; }

			/// <summary>
			/// pre�O�̃����_�����O�o�b�t�@���擾
			/// </summary>
			/// <param name="pre"></param>
			/// <returns></returns>
			RenderingBuffer3D& Get(int pre);

			int GetIdx()const { return idx; }

		private:
			RenderingBuffer3D buffers[BUFFERSIZE];

			int idx = 0;
		};
	}
}
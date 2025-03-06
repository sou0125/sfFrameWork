#pragma once
#include "D3D.h"

#include <assimp/texture.h>

namespace sf
{
	//�e�N�X�`�����\�[�X�N���X
	class ITexture :public dx::D3D
	{
	public:
		virtual ~ITexture();

		void Release()override;

		void SetGPU(int slot, ID3D11DeviceContext* d3dContext) const;

	//protected:
		ID3D11ShaderResourceView* srv = nullptr;
	};

	//�O���t�@�C������ǂݍ��񂾃e�N�X�`���N���X
	class Texture :public ITexture
	{
	public:
		bool LoadTextureFromFile(std::string path);

		int GetWidth()const { return w; }
		int GetHeight()const { return h; }

	private:
		int w = 0;
		int h = 0;

		std::string fileName;
	};

	//����������ǂݍ��񂾃e�N�X�`���N���X
	class TextureMemory :public ITexture
	{
	public:
		bool LoadTexture(const aiTexture* texture);
	};
}
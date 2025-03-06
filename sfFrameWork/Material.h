#pragma once
#include "SafePtr.h"
#include "Texture.h"
#include "ConstBuffer.h"
#include <assimp/material.h>
#include <assimp/texture.h>
namespace sf
{
	//�}�e���A���N���X
	class Material
	{
	public:
		/// <summary>
		/// GPU�փ}�e���A�����𑗂�
		/// </summary>
		/// <param name="d3dContext"></param>
		/// <param name="diffuseTexture">diffuse�e�N�X�`���̗L��</param>
		/// <param name="normalTexture">�@���e�N�X�`���̗L��</param>
		void SetGPU(ID3D11DeviceContext* d3dContext, bool diffuseTexture = false, bool normalTexture = false)const;

	public:
		DirectX::XMFLOAT4 diffuseColor = DirectX::XMFLOAT4(1, 1, 1, 1);

		bool shadow = false;

		sf::SafePtr<Texture> texture;
	};
}
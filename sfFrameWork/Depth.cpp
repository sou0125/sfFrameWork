#include "Depth.h"
#include "DirectX11.h"
#include "Debug.h"

sf::dx::Depth::~Depth()
{
	Release();
}

HRESULT sf::dx::Depth::Create(int x, int y)
{
	HRESULT hr;

	ID3D11Device* d3dDevice = DirectX11::Instance()->GetMainDevice();

	// �[�x�X�e���V���o�b�t�@���쐬
	// ���[�x�o�b�t�@�iZ�o�b�t�@�j�����s�𔻒肵�đO��֌W�𐳂����`��ł���
	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = x;
	txDesc.Height = y;
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;
	hr = d3dDevice->CreateTexture2D(&txDesc, NULL, &depthStencilTexture);
	if (FAILED(hr))
	{
		throw std::runtime_error("�[�x�e�N�X�`���̍쐬�Ɏ��s���܂���");
		return hr;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;
	hr = d3dDevice->CreateDepthStencilView(depthStencilTexture, &dsDesc, &depthStencilView);
	if (FAILED(hr))
	{
		throw std::runtime_error("�[�x�X�e���V���r���[�̍쐬�Ɏ��s���܂���");
		return hr;
	}

	debug::Debug::LogSafety("�[�x�o�b�t�@�̍쐬�ɐ������܂���");

	return hr;
}

void sf::dx::Depth::Release()
{
	SAFE_RELEASE(depthStencilTexture);
	SAFE_RELEASE(depthStencilView);
}

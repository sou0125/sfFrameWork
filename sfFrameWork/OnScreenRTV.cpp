#include "OnScreenRTV.h"
#include "sf.h"
#include "DirectX11.h"

HRESULT sf::dx::OnScreenRTV::Create()
{
	ID3D11Device* d3dDevice = DirectX11::Instance()->GetMainDevice().GetDevice();
	IDXGISwapChain* d3dSwapChain = DirectX11::Instance()->GetMainDevice().GetSwapChain();

	ID3D11Texture2D* renderTarget = NULL;
	HRESULT hr = d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);

	if (FAILED(hr))
	{
		throw std::runtime_error("�o�b�N�o�b�t�@�̎擾�Ɏ��s���܂���");
		return hr;
	}

	hr = d3dDevice->CreateRenderTargetView(renderTarget, NULL, &rtv);
	if (FAILED(hr))
	{
		SAFE_RELEASE(renderTarget);
		throw std::runtime_error("�I���X�N���[�������_�[�^�[�Q�b�g�̍쐬�Ɏ��s���܂���");
		return hr;
	}
	SAFE_RELEASE(renderTarget);

	sf::debug::Debug::LogSafety("�I���X�N���[�������_�[�^�[�Q�b�g�̍쐬�ɐ������܂���");
}

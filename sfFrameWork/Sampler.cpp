#include "Sampler.h"
#include "DirectX11.h"

sf::dx::Sampler::~Sampler()
{
	Release();
}

void sf::dx::Sampler::Release()
{
	SAFE_RELEASE(d3dSampler);
}

HRESULT sf::dx::Sampler::Create(D3D11_TEXTURE_ADDRESS_MODE u, D3D11_TEXTURE_ADDRESS_MODE v)
{
	/*
		---�T���v���[�̃p�����[�^���---

	�ZD3D11_TEXTURE_ADDRESS_WRAP:
	�e�N�X�`������UV���W�Ɍ��炸���݂��A���]���J��Ԃ�

	�ZD3D11_TEXTURE_ADDRESS_MIRROR:
	�e�N�X�`������UV���W�Ɍ��炸���݂��A���],���]���J��Ԃ�

	�ZD3D11_TEXTURE_ADDRESS_CLAMP:
	�e�N�X�`������UV���W0.0f�`1.0f�̂ݑ��݂���

	�ZD3D11_TEXTURE_ADDRESS_BORDER:
	UV���W0.0f�`1.0f�͈̔͂̂݃N���b�s���O�����B���̑��̗̈�͕`�悳��Ȃ�

	�ZD3D11_TEXTURE_ADDRESS_MIRROR_ONCE:
	�e�N�X�`������UV���W-1.0f�`1.0f�ɑ��݂��A���],���]���đ��݂���
	*/

	D3D11_SAMPLER_DESC smpDesc;
	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = u;		//U���W�̃p�����[�^
	smpDesc.AddressV = v;		//V���W�̃p�����[�^
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	HRESULT hr = DirectX11::Instance()->GetMainDevice().GetDevice()->CreateSamplerState(&smpDesc, &d3dSampler);

	if (FAILED(hr))
	{
		throw std::runtime_error("�T���v���[�̍쐬�Ɏ��s���܂���");
		return hr;
	}

	return hr;
}

void sf::dx::Sampler::SetGPU(ID3D11DeviceContext* d3dContext) const
{
	d3dContext->VSSetSamplers(0, 1, &d3dSampler);
	d3dContext->PSSetSamplers(0, 1, &d3dSampler);
	//d3dContext->GSSetSamplers(0, 1, &d3dSampler);
	//d3dContext->HSSetSamplers(0, 1, &d3dSampler);
	//d3dContext->DSSetSamplers(0, 1, &d3dSampler);
}

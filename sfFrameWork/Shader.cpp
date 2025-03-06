#include "Shader.h"
#include "sf.h"
#include <sstream>

HRESULT sf::dx::shader::Shader::LoadCSO(std::string fileName)
{
	HRESULT hr = E_FAIL;

	// �t�@�C����ǂݍ���
	FILE* fp;
	fopen_s(&fp, fileName.c_str(), "rb");
	if (!fp)
	{
		throw std::runtime_error("CSO�t�@�C���̓ǂݍ��݂Ɏ��s���܂���:" + fileName);
		return hr;
	}

	// �t�@�C���̃T�C�Y�𒲂ׂ�
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// �������ɓǂݍ���
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// �V�F�[�_�[�쐬
	hr = Make(pData, fileSize);

	// �I������
	if (pData) { delete[] pData; }

	if (FAILED(hr))
	{
		throw std::runtime_error("�V�F�[�_�[�̍쐬�Ɏ��s���܂���:" + fileName);
		return hr;
	}

	sf::debug::Debug::LogSafety("�V�F�[�_�[�̍쐬�ɐ������܂���:" + fileName);

	return hr;
}

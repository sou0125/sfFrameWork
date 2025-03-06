#pragma once
#include <vector>
#include <string>
#include "TextFile.h"
#include "BinaryFile.h"

namespace sf
{
	namespace file
	{
		//wstring->string
		std::string wstring2string(const std::wstring& src);

		//string->wstring
		std::wstring string2wstring(const std::string& src);

		//�t�H���_���̃t�@�C���p�X���擾����֐�
		std::vector<std::string> SearchFolder(std::string folder);

		//�t�H���_���̑S�Ẵt�@�C���p�X���擾����֐�
		std::vector<std::string> SearchFolderAll(std::string folder);

		//�t�@�C���̊g���q���擾����֐�
		std::string GetExtension(const std::string path);

		//���̃t�@�C�����t�H���_�����f����֐�
		bool IsFolder(std::string path);

		//�t�H���_�쐬�֐�
		bool CreateFolder(std::string path);

		//�t�@�C���폜�֐�
		bool DeleteFile(std::string path);

		//�t�H���_�폜�֐�(�t�@�C��������ꍇ�A�����ō폜����܂�)
		bool DeleteFolder(std::string path);

		std::vector<std::string> ReadFile(std::string path);

		void WriteFile(std::string path, std::vector<std::string> data);
	}
}
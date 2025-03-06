#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "File.h"
#include <filesystem>

#include <locale>
#include <codecvt>
#include <iostream>

std::string sf::file::wstring2string(const std::wstring& src)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > converter;
	return converter.to_bytes(src);
}

std::wstring sf::file::string2wstring(const std::string& src)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(src);
}

std::vector<std::string> sf::file::SearchFolder(std::string folder)
{
	std::vector<std::string> pathes;
	if (!std::filesystem::exists(folder))
	{
		return pathes;
	}

	// �f�B���N�g�����̃t�@�C���ƃt�H���_���C�e���[�g
	for (const auto& entry : std::filesystem::directory_iterator(folder)) {
		pathes.push_back(wstring2string(entry.path().c_str()));
	}

	return pathes;
}

std::vector<std::string> sf::file::SearchFolderAll(std::string folder)
{
	std::vector<std::string> pathes, ret;

	pathes = SearchFolder(folder);

	for (const auto& i : pathes) {
		//�t�H���_�Ȃ�
		if (IsFolder(i))
		{
			//�ċA�Ăяo��
			std::vector<std::string> childPathes = SearchFolderAll(i);

			//�z��m��
			ret.reserve(ret.size() + childPathes.size());

			//ret�̌��ɂ�childPathes�̗v�f���R�s�[
			std::copy(childPathes.begin(), childPathes.end(), std::back_inserter(ret));
		}
		else
		{
			//�g���q������Ζ߂�l�ɑ}��
			ret.push_back(i);
		}
	}

	return ret;
}

std::string sf::file::GetExtension(const std::string path)
{
	//'.'�̈ʒu����납�猟��
	size_t dotPos = path.rfind('.');

	//'.' ��������Ȃ��ꍇ�͋�̕������Ԃ�
	if (dotPos == std::string::npos) {
		return "";
	}

	// �t�@�C�����̍Ō�ɂ���ꍇ�͋�̕������Ԃ�
	if (dotPos == path.length() - 1)
	{
		return "";
	}

	int e1 = path.rfind('\\');
	int e2 = path.rfind('/');
	int e = e1;
	if (e1 < e2)
	{
		e = e2;
	}

	//���΃p�X(./)(../)��'.'���I�΂ꂽ�ꍇ->'.'�̌��'\\'�͗����
	if (dotPos < e)
	{
		return "";
	}

	//�g���q��Ԃ��i'.' �̎��̕�������Ō�܂Łj
	return path.substr(dotPos + 1);
}

bool sf::file::IsFolder(std::string path)
{
	return GetExtension(path).empty();
}

bool sf::file::CreateFolder(std::string path)
{
	return std::filesystem::create_directory(path);
}

bool sf::file::DeleteFile(std::string path)
{
	//���̃t�@�C�������邩�m�F
	if (std::filesystem::exists(path)) {

		try {
			std::filesystem::remove(path);
			return true;
		}
		catch (const std::exception& e) {
			return false;
		}

		return std::filesystem::remove(path);
	}
	else
	{
		return false;
	}
}

bool sf::file::DeleteFolder(std::string path)
{
	std::vector<std::string> pathes = file::SearchFolder(path);
	for (const auto& i : pathes) {

		//�g���q�������
		if (!IsFolder(i))
		{
			//�t�@�C���폜
			if (!DeleteFile(i))
			{
				return false;
			}
		}
		else
		{
			//�t�H���_���̃t�@�C�����폜
			if (DeleteFolder(i))
			{
				return false;
			}

			//�t�H���_�{�̂��폜
			if (DeleteFile(i))
			{
				return false;
			}
		}
	}

	return DeleteFile(path);
}

std::vector<std::string> sf::file::ReadFile(std::string path)
{
	std::vector<std::string> data{};
	FILE* fp = NULL;
	fopen_s(&fp, path.c_str(), "r");

	if (!fp)
	{
		return data;
	}

	while (true)
	{
		char c[256]{};

		fgets(c, 256, fp);

		std::string str = c;

		//�f�[�^�������Ȃ��
		if (str.empty())
		{
			break;
		}

		//���s�R�[�h�𖳂���
		if (str.back() == '\n')
		{
			str.erase(str.end() - 1);
		}
		data.push_back(str);
	}

	fclose(fp);

	return data;
}

void sf::file::WriteFile(std::string path, std::vector<std::string> data)
{

}

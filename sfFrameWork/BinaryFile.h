#pragma once
#include "FileBase.h"

namespace sf
{
	namespace file
	{
		class BinaryFile :FileBase
		{
		public:
			BinaryFile(std::string _fileName);
			~BinaryFile();

			void Clean();

			//�ꊇ�f�[�^��������
			template<typename T>
			bool WriteAll(const T& data)
			{
				if (fp)
				{
					fclose(fp);
					fp = nullptr;
				}

				fopen_s(&fp, fileName.c_str(), "wb");

				if (!fp)
				{
					return false;
				}

				fwrite(&data, sizeof(T), 1, fp);

				fclose(fp);
			}

			//�f�[�^�ǋL��������
			template<typename T>
			bool Write(const T& data)
			{
				if (!fp)
				{
					fopen_s(&fp, fileName.c_str(), "ab");
				}

				if (!fp)
				{
					return false;
				}

				fwrite(&data, sizeof(T), 1, fp);
			}

			//�z��f�[�^�ǋL��������
			template<typename T>
			bool WriteArray(const T* data, unsigned int arraySize)
			{
				if (!fp)
				{
					fopen_s(&fp, fileName.c_str(), "ab");
				}

				if (!fp)
				{
					return false;
				}

				fwrite(&arraySize, sizeof(unsigned int), 1, fp);
				fwrite(data, sizeof(T), arraySize, fp);
			}

			//�ꊇ�f�[�^�ǂݍ���
			template<typename T>
			bool ReadAll(T* buf)
			{
				if (fp)
				{
					fclose(fp);
					fp = nullptr;
				}

				fopen_s(&fp, fileName.c_str(), "rb");

				if (!fp)
				{
					return false;
				}

				fread(buf, sizeof(T), 1, fp);

				fclose(fp);

				return true;
			}

			//�f�[�^�ǂݍ���
			template<typename T>
			bool Read(T* buf)
			{
				if (!fp)
				{
					fopen_s(&fp, fileName.c_str(), "rb");
				}
				if (!fp)
				{
					return false;
				}

				fread(buf, sizeof(T), 1, fp);

				return true;
			}

			//�z��f�[�^�ǂݍ���
			template<typename T>
			int ReadArray(T* data)
			{
				if (!fp)
				{
					fopen_s(&fp, fileName.c_str(), "rb");
				}

				if (!fp)
				{
					return 0;
				}

				int arraySize = 0;
				fread(&arraySize, sizeof(unsigned int), 1, fp);
				fread(data, sizeof(T), arraySize, fp);

				return arraySize;
			}

		private:
			FILE* fp = nullptr;
		};
	}
}

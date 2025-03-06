#pragma once
#include <string>
#include <vector>
#include <mutex>
#include <queue>
#include "Vector3.h"
#include "File.h"

#define DEBUG_LINE	(true)

namespace sf
{

	//�������UTF8�ɕϊ�����֐�
	std::string ConvertToUTF8(const std::string& sjis_str);
	std::wstring Utf8ToUtf16(const std::string& utf8);
	std::string Utf16ToShiftJIS(const std::wstring& utf16);
	std::string Utf8ToShiftJIS(const std::string& utf8);

	namespace debug
	{
		//�f�o�b�O����
		class Debug
		{
		private:
			struct LogData
			{
				enum LogKind
				{
					Normal,
					Safety,
					Warning,
					Error,
					Engine,
				};

				//���O�̃e�L�X�g
				std::string log;

				//���O�̃e�L�X�g(u8�R���o�[�g��)
				std::string logu8;

				//�������e�L�X�g����������
				std::string timeText;
				LogKind logKind = LogKind::Normal;
			};

		public:
			struct LineData
			{
				DirectX::XMFLOAT4 p1;
				DirectX::XMFLOAT4 p2;
				DirectX::XMFLOAT4 color;
			};

		public:
			/// <summary>
			/// ���O���O���t�@�C���ɏ�������
			/// </summary>
			static void WriteLogFile();

			/// <summary>
			/// ���O�̏o��
			/// </summary>
			/// <param name="str"></param>
			static void Log(std::string str);
			static void Log(const Vector3& v);

			/// <summary>
			/// �������O�̏o��
			/// </summary>
			/// <param name="str"></param>
			static void LogSafety(std::string str);

			/// <summary>
			/// �x�����O�̏o��
			/// </summary>
			/// <param name="str"></param>
			static void LogWarning(std::string str);

			/// <summary>
			/// �G���[���O�̏o��
			/// </summary>
			/// <param name="str"></param>
			static void LogError(std::string str);

			/// <summary>
			/// �G���W�����O�̏o��
			/// </summary>
			/// <param name="str"></param>
			static void LogEngine(std::string str);

			/// <summary>
			/// ���̕`��
			/// </summary>
			/// <param name="p1"></param>
			/// <param name="p2"></param>
			/// <param name="color"></param>
			static void DrawLine(Vector3 p1, Vector3 p2, DirectX::XMFLOAT4 color);

			static void DrawLog();

			/// <summary>
			/// �S���O�̏o��
			/// </summary>
			static void TraceLog();

		private:
			static std::string GetTime();

			static void AddLog(LogData data);

		private:
			static std::vector<LogData> logDatas;
			static std::queue<LineData> lineDatas;
			static std::mutex mtx;

			static sf::file::TextFile textFile;
		};
	}
}

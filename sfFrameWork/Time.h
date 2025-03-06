#pragma once
#define FRAME_RATE (60)
#include <Windows.h>
namespace sf
{
	//�A�v���P�[�V�����̎��ԊǗ�(Static�N���X)
	class Time
	{
	public:
		static void Init();

		//���Ԃ̍X�V����(1�t���[���o�߂Ȃ�true)
		static bool Update();

		static long long GetPassTime() { return passTime; }

		//���ۂ�FPS�擾(�ݒ�l�ł͂Ȃ�)
		static double GetFPS();

		static float GetSetingFPS() { return setfps; }

		//FPS�̐ݒ�
		static void SetFPS(float _fps);

		static float DeltaTime();

	private:

		static float setfps;

		// FPS�\���p�ϐ�
		static int fpsCounter;
		static long long oldTick;
		static long long nowTick;

		// FPS�Œ�p�ϐ�
		static LARGE_INTEGER liWork; // �֐�����l���󂯎��p
		static long long frequency; // �v�����x

		// �P�t���[��������̃J�E���g�l���v�Z
		static long long numCount_1frame;

		// ���ݎ��ԁi�P�ʁF�J�E���g�j���擾
		static long long oldCount;
		static long long nowCount;

		static long long passTime;
	};
}
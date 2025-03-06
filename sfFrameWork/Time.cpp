#include "Time.h"
float sf::Time::setfps = FRAME_RATE;

// FPS�\���p�ϐ�
int sf::Time::fpsCounter;
long long sf::Time::oldTick;
long long sf::Time::nowTick;

// FPS�Œ�p�ϐ�
LARGE_INTEGER sf::Time::liWork; // �֐�����l���󂯎��p
long long sf::Time::frequency; // �v�����x

// �P�t���[��������̃J�E���g�l���v�Z
long long sf::Time::numCount_1frame;

// ���ݎ��ԁi�P�ʁF�J�E���g�j���擾
long long sf::Time::oldCount;
long long sf::Time::nowCount;

long long sf::Time::passTime;

void sf::Time::Init()
{
	// FPS�\���p�ϐ�
	fpsCounter = 0;
	oldTick = GetTickCount64();		//���ݎ��Ԃ�ۑ�
	nowTick = oldTick;				// ���ݎ��Ԏ擾�p

	// �v�����x���擾
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;	// �P�b������̉𑜓x������

	// �P�t���[��������̃J�E���g�l���v�Z
	numCount_1frame = frequency / FRAME_RATE;

	// ���ݎ��ԁi�P�ʁF�J�E���g�j���擾
	QueryPerformanceCounter(&liWork);
	oldCount = liWork.QuadPart;
	nowCount = oldCount;
}

bool sf::Time::Update()
{
	// 1 / FRAME_RATE �b�o�߂�����
	QueryPerformanceCounter(&liWork);
	nowCount = liWork.QuadPart;			// ���ݎ��Ԃ��擾�i�P�ʁF�J�E���g�j

	if (nowCount >= oldCount + numCount_1frame)
	{
		fpsCounter++; // �Q�[�����[�v�������Z

		passTime = nowCount - oldCount;

		oldCount = nowCount;

		return true;
	}
	else
	{
		return false;
	}
}

double sf::Time::GetFPS()
{
	long long t = GetPassTime();
	t *= 0.001;
	double ret = t;
	ret = 1.0f / ret;
	ret *= 10000;
	return ret;
}

void sf::Time::SetFPS(float _fps)
{
	setfps = _fps;

	LARGE_INTEGER _liWork;
	// �v�����x���擾
	QueryPerformanceFrequency(&_liWork);
	long long _frequency = _liWork.QuadPart;	// �P�b������̉𑜓x������

	// �P�t���[��������̃J�E���g�l���v�Z
	numCount_1frame = _frequency / _fps;
}

float sf::Time::DeltaTime()
{
	return static_cast<float>(1.0 / GetFPS());
}

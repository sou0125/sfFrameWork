#include "SwatMotionArray.h"

void app::test::SwatMotionArray::LoadMotions()
{
	motionDatas.resize(2);

	//���[�V�����f�[�^�̓ǂݍ���
	motionDatas[0].LoadMotion("Assets\\Motion\\Idol.fbx");
	motionDatas[1].LoadMotion("Assets\\Motion\\Walk.fbx");
}

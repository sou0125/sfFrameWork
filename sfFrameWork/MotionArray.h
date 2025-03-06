#pragma once
#include "MotionData.h"
#include <vector>
namespace sf
{
	namespace motion
	{
		//1�̃L�����N�^�[���g�����[�V�������܂Ƃ܂����N���X
		class MotionArray
		{
		public:
			virtual void LoadMotions() = 0;

			const std::vector<MotionData>& GetMotionDatas()const { return motionDatas; }

		protected:
			std::vector<MotionData> motionDatas;
		};
	}
}
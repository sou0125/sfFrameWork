#pragma once
#include "App.h"
namespace app
{
	namespace test
	{
		class ChangeMotionComponent :public sf::Component
		{
		public:
			void Begin()override;

		private:
			void Update();

		private:
			sf::command::Command<> updateCommand;

			//Motion�R���|�[�l���g�ۑ��p�ϐ�
			sf::SafePtr<sf::motion::Motion> motion;
		};
	}
}
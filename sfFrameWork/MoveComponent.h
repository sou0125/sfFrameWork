#pragma once
#include "App.h"
namespace app
{
	namespace test
	{
		class MoveComponent :public sf::Component
		{
		public:
			void Begin()override;

		private:
			//���t���[������
			void Update(const sf::command::ICommand& command);

		private:
			//�X�V�R�}���h
			sf::command::Command<> updateCommand;
		};
	}
}
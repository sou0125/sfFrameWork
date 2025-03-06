#pragma once
#include "App.h"
namespace app
{
	namespace test
	{
		class SceneChangeComponent :public sf::Component
		{
		public:
			void Begin()override;

		private:
			void Update();

		private:
			//�X�V�R�}���h
			sf::command::Command<> updateCommand;

			//�V�K�V�[��
			sf::SafePtr<sf::IScene> scene;
		};
	}
}
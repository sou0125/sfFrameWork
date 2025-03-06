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
			//更新コマンド
			sf::command::Command<> updateCommand;

			//新規シーン
			sf::SafePtr<sf::IScene> scene;
		};
	}
}
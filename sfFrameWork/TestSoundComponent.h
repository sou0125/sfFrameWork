#pragma once
#include "App.h"
namespace app
{
	namespace test
	{
		class TestSoundComponent :public sf::Component
		{
		public:
			void Begin()override;

		private:
			void Update();

		private:
			//更新コマンド
			sf::command::Command<> updateCommand;

			//音再生コンポーネント(AudioSource)
			sf::SafePtr<sf::sound::SoundPlayer> soundPlayer;

			//音源リソース(AudioClip)
			sf::sound::SoundResource resource;
		};
	}
}
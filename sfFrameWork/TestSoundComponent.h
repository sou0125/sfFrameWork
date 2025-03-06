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
			//�X�V�R�}���h
			sf::command::Command<> updateCommand;

			//���Đ��R���|�[�l���g(AudioSource)
			sf::SafePtr<sf::sound::SoundPlayer> soundPlayer;

			//�������\�[�X(AudioClip)
			sf::sound::SoundResource resource;
		};
	}
}
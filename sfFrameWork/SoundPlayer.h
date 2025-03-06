#pragma once
#include "Component.h"
#include "SoundResource.h"
namespace sf
{
	namespace sound
	{
		//音再生コンポーネント
		class SoundPlayer :public Component
		{
		public:
			~SoundPlayer();
			void DeActivate()override;

			void Play();
			void Stop();

			void SetResource(sf::ref::Ref<SoundResource> _v);

		private:
			void SetSound();

		private:
			sf::ref::Ref<SoundResource> resource;

			IXAudio2SourceVoice* source = nullptr;
		};
	}
}
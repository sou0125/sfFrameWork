#include "TestSoundComponent.h"

void app::test::TestSoundComponent::Begin()
{
	//Update関数の設定
	updateCommand.Bind(std::bind(&TestSoundComponent::Update, this));

	//音再生コンポーネント追加
	soundPlayer = actorRef.Target()->AddComponent<sf::sound::SoundPlayer>();

	//音の読み込み
	resource.LoadSound("Assets\\sound\\testsound.wav");

	//音の設定
	soundPlayer->SetResource(resource);
}

void app::test::TestSoundComponent::Update()
{
	//Bキーが押された
	if (SInput::Instance().GetKeyDown(Key::KEY_B))
	{
		//音の再生
		soundPlayer->Play();
	}
}

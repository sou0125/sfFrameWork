#include "TestSoundComponent.h"

void app::test::TestSoundComponent::Begin()
{
	//Update�֐��̐ݒ�
	updateCommand.Bind(std::bind(&TestSoundComponent::Update, this));

	//���Đ��R���|�[�l���g�ǉ�
	soundPlayer = actorRef.Target()->AddComponent<sf::sound::SoundPlayer>();

	//���̓ǂݍ���
	resource.LoadSound("Assets\\sound\\testsound.wav");

	//���̐ݒ�
	soundPlayer->SetResource(resource);
}

void app::test::TestSoundComponent::Update()
{
	//B�L�[�������ꂽ
	if (SInput::Instance().GetKeyDown(Key::KEY_B))
	{
		//���̍Đ�
		soundPlayer->Play();
	}
}

#include "SceneChangeComponent.h"
#include "DynamicScene.h"

void app::test::SceneChangeComponent::Begin()
{
	updateCommand.Bind(std::bind(&SceneChangeComponent::Update, this));
}

void app::test::SceneChangeComponent::Update()
{
	//�X�y�[�X�L�[�������ꂽ��
	if (SInput::Instance().GetKeyDown(Key::SPACE))
	{
		//�V�[������������ɑ��݂��Ȃ����
		if (scene.isNull())
		{
			//�V�[�����X�^���o�C��Ԃɂ���
			scene = DynamicScene::StandbyScene();
		}
		else
		{
			//�V�[�������̉�����Ă�����
			if (scene->IsActivate())
			{
				//�V�[�����폜����
				scene->DeActivate();
				scene = nullptr;
			}
			else
			{
				//�V�[���̓ǂݍ��݂��������Ă�����
				if (scene->StandbyThisScene())
				{
					//�V�[�������̉�������
					scene->Activate();
				}
				else
				{
					sf::debug::Debug::LogWarning("�V�[���ǂݍ��݂��������Ă��܂���I");
				}
			}
		}
	}
}

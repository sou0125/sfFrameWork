#include "ChangeMotionComponent.h"
#include "SwatMotionArray.h"

void app::test::ChangeMotionComponent::Begin()
{
	updateCommand.Bind(std::bind(&ChangeMotionComponent::Update, this));

	//Motion�R���|�[�l���g���擾
	motion = actorRef.Target()->GetComponent<sf::motion::Motion>();
}

void app::test::ChangeMotionComponent::Update()
{
	//1�L�[�������ꂽ��
	if (SInput::Instance().GetKeyDown(Key::KEY_1))
	{
		motion->SetMotion(SwatMotionArray::ID_Idle);
	}

	//2�L�[�������ꂽ��
	if (SInput::Instance().GetKeyDown(Key::KEY_2))
	{
		motion->SetMotion(SwatMotionArray::ID_Walk);
	}
}

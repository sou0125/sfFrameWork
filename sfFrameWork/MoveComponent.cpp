#include "MoveComponent.h"

void app::test::MoveComponent::Begin()
{
	updateCommand.Bind(std::bind(&MoveComponent::Update, this, std::placeholders::_1));
}

void app::test::MoveComponent::Update(const sf::command::ICommand& command)
{
	const float speed = 1.0f;

	if (SInput::Instance().GetKey(Key::KEY_W))
	{
		//W�L�[�������ꂽ���̏���

		//���W�̎擾
		auto position = actorRef.Target()->transform.GetPosition();

		//���l�̌v�Z
		position += Vector3::Forward * speed * sf::Time::DeltaTime();

		//���W�̔��f
		actorRef.Target()->transform.SetPosition(position);
	}
	if (SInput::Instance().GetKey(Key::KEY_A))
	{
		//A�L�[�������ꂽ���̏���

		//���W�̎擾
		auto position = actorRef.Target()->transform.GetPosition();

		//���l�̌v�Z
		position += Vector3::Left * speed * sf::Time::DeltaTime();

		//���W�̔��f
		actorRef.Target()->transform.SetPosition(position);
	}
	if (SInput::Instance().GetKey(Key::KEY_S))
	{
		//S�L�[�������ꂽ���̏���

		//���W�̎擾
		auto position = actorRef.Target()->transform.GetPosition();

		//���l�̌v�Z
		position += Vector3::Back * speed * sf::Time::DeltaTime();

		//���W�̔��f
		actorRef.Target()->transform.SetPosition(position);
	}
	if (SInput::Instance().GetKey(Key::KEY_D))
	{
		//D�L�[�������ꂽ���̏���

		//���W�̎擾
		auto position = actorRef.Target()->transform.GetPosition();

		//���l�̌v�Z
		position += Vector3::Right * speed * sf::Time::DeltaTime();

		//���W�̔��f
		actorRef.Target()->transform.SetPosition(position);
	}

	if (SInput::Instance().GetKeyDown(Key::SPACE))
	{
		command.UnBind();
	}
}

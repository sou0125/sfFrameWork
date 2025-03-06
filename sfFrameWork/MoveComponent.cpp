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
		//Wキーが押された時の処理

		//座標の取得
		auto position = actorRef.Target()->transform.GetPosition();

		//数値の計算
		position += Vector3::Forward * speed * sf::Time::DeltaTime();

		//座標の反映
		actorRef.Target()->transform.SetPosition(position);
	}
	if (SInput::Instance().GetKey(Key::KEY_A))
	{
		//Aキーが押された時の処理

		//座標の取得
		auto position = actorRef.Target()->transform.GetPosition();

		//数値の計算
		position += Vector3::Left * speed * sf::Time::DeltaTime();

		//座標の反映
		actorRef.Target()->transform.SetPosition(position);
	}
	if (SInput::Instance().GetKey(Key::KEY_S))
	{
		//Sキーが押された時の処理

		//座標の取得
		auto position = actorRef.Target()->transform.GetPosition();

		//数値の計算
		position += Vector3::Back * speed * sf::Time::DeltaTime();

		//座標の反映
		actorRef.Target()->transform.SetPosition(position);
	}
	if (SInput::Instance().GetKey(Key::KEY_D))
	{
		//Dキーが押された時の処理

		//座標の取得
		auto position = actorRef.Target()->transform.GetPosition();

		//数値の計算
		position += Vector3::Right * speed * sf::Time::DeltaTime();

		//座標の反映
		actorRef.Target()->transform.SetPosition(position);
	}

	if (SInput::Instance().GetKeyDown(Key::SPACE))
	{
		command.UnBind();
	}
}

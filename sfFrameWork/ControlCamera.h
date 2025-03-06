#pragma once
#include "App.h"
namespace app
{
	//�}�E�X�ŃJ�����ړ�����R���|�[�l���g
	class ControlCamera :public sf::Component
	{
	public:
		void Begin()override;

	private:
		void Update();

		void Rotation();
		void Move();

	private:
		sf::command::Command<> command;

		Vector3 rot;

		sf::del::DELEGATE<ControlCamera> del = this;

		POINT pre{};
	};
}
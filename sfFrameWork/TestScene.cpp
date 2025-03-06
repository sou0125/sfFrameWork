#include "TestScene.h"
#include "MoveComponent.h"
#include "SceneChangeComponent.h"
#include "TestCanvas.h"
#include "TestSoundComponent.h"

void app::test::TestScene::Init()
{
	sf::debug::Debug::Log("TestScene��Init�ł�");

	//�A�N�^�[����
	auto a_cube = Instantiate();

	//���b�V���R���|�[�l���g�̒ǉ�
	auto m_cube = a_cube.Target()->AddComponent<sf::Mesh>();

	//�`��̐ݒ�
	m_cube->SetGeometry(g_cube);

	//�ړ��R���|�[�l���g�ǉ�
	a_cube.Target()->AddComponent<MoveComponent>();

	//�V�[���؂�ւ��R���|�[�l���g�ǉ�
	a_cube.Target()->AddComponent<SceneChangeComponent>();

	//Canvas�ǉ�
	a_cube.Target()->AddComponent<TestCanvas>();

	//���쉹�Đ��R���|�[�l���g�ǉ�
	a_cube.Target()->AddComponent<TestSoundComponent>();
}

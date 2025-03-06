#include "DynamicScene.h"
#include "ChangeMotionComponent.h"

void app::test::DynamicScene::Init()
{
	////�A�N�^�[����
	//auto a_sphere = Instantiate();

	////���W�ݒ�
	//a_sphere.Target()->transform.SetPosition(Vector3(0, 2, 0));

	////���b�V���R���|�[�l���g�̒ǉ�
	//auto m_sphere = a_sphere.Target()->AddComponent<sf::Mesh>();

	////�`��̐ݒ�
	//m_sphere->SetGeometry(g_sphere);

	////�}�e���A���F�ύX
	//m_sphere->material.diffuseColor = DirectX::XMFLOAT4(1, 0, 0, 1);



	//���f���ǂݍ���
	g_human.Load();

	//���[�V�����ǂݍ���
	ma_human.LoadMotions();

	//�A�N�^�[����
	auto a_human = Instantiate();

	//�X�P�[���ݒ�
	a_human.Target()->transform.SetScale(Vector3::One * 0.01f);

	//���b�V���R���|�[�l���g�̒ǉ�
	auto m_human = a_human.Target()->AddComponent<sf::Mesh>();

	//�`��̐ݒ�
	m_human->SetGeometry(g_human);

	//���[�V�����R���|�[�l���g�ǉ�
	auto mo_human = a_human.Target()->AddComponent<sf::motion::Motion>();

	//���[�V�����R���|�[�l���g�Ƀ��[�V�����A���C��ݒ�
	mo_human->SetGeomeyryMotion(g_human, ma_human);

	//���[�V�����؂�ւ��R���|�[�l���g�ǉ�
	a_human.Target()->AddComponent<ChangeMotionComponent>();
}

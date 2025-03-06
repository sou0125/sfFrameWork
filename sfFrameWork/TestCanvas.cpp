#include "TestCanvas.h"

void app::test::TestCanvas::Begin()
{
	//���N���X��Begin��K���Ăяo���K�v������܂�
	sf::ui::Canvas::Begin();

	//�e�N�X�`���̓ǂݍ���
	texture.LoadTextureFromFile("Assets\\Texture\\myIcon01.png");

	//UI�̒ǉ�
	auto i_squere = AddUI<sf::ui::Image>();

	//���W�̐ݒ�
	i_squere->transform.SetPosition(Vector3(200, 0, 0));

	//�e�N�X�`���̓\��t��
	i_squere->material.texture = &texture;
}

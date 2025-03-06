#include "TestCanvas.h"

void app::test::TestCanvas::Begin()
{
	//基底クラスのBeginを必ず呼び出す必要があります
	sf::ui::Canvas::Begin();

	//テクスチャの読み込み
	texture.LoadTextureFromFile("Assets\\Texture\\myIcon01.png");

	//UIの追加
	auto i_squere = AddUI<sf::ui::Image>();

	//座標の設定
	i_squere->transform.SetPosition(Vector3(200, 0, 0));

	//テクスチャの貼り付け
	i_squere->material.texture = &texture;
}

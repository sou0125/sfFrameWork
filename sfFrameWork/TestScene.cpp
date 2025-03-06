#include "TestScene.h"
#include "MoveComponent.h"
#include "SceneChangeComponent.h"
#include "TestCanvas.h"
#include "TestSoundComponent.h"

void app::test::TestScene::Init()
{
	sf::debug::Debug::Log("TestSceneのInitです");

	//アクター生成
	auto a_cube = Instantiate();

	//メッシュコンポーネントの追加
	auto m_cube = a_cube.Target()->AddComponent<sf::Mesh>();

	//形状の設定
	m_cube->SetGeometry(g_cube);

	//移動コンポーネント追加
	a_cube.Target()->AddComponent<MoveComponent>();

	//シーン切り替えコンポーネント追加
	a_cube.Target()->AddComponent<SceneChangeComponent>();

	//Canvas追加
	a_cube.Target()->AddComponent<TestCanvas>();

	//自作音再生コンポーネント追加
	a_cube.Target()->AddComponent<TestSoundComponent>();
}

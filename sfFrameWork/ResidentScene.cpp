#include "ResidentScene.h"
#include "TestScene.h"
#include "ControlCamera.h"

void app::ResidentScene::Init()
{
	//メインカメラ
	sf::ref::Ref<sf::Actor> mainActor = Instantiate();
	mainActor.Target()->transform.SetPosition(Vector3(0, 1.5f, -2.0f));
	mainActor.Target()->AddComponent<ControlCamera>();
	sf::SafePtr<sf::Camera> mainCamera = mainActor.Target()->AddComponent<sf::Camera>();
	sf::Camera::main = mainCamera.Get();

	//影カメラ
	sf::ref::Ref<sf::Actor> shadowActor = Instantiate();
	shadowActor.Target()->transform.SetPosition(Vector3(0, 5, 0));
	shadowActor.Target()->transform.SetRotation(Vector3(90, 0, 0));
	sf::SafePtr<sf::Camera> shadowCamera = shadowActor.Target()->AddComponent<sf::Camera>();
	sf::Camera::shadow = shadowCamera.Get();

	LoadLoadingScene();
}

void app::ResidentScene::LoadLoadingScene()
{
	//初期シーンはメインスレッド内でロード、アクティベートさせる
	auto scene = test::TestScene::StandbyScene();

	while (1)
	{
		if (scene->StandbyThisScene())
		{
			break;
		}
	}
	scene->Activate();
}

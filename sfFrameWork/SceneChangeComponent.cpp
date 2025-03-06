#include "SceneChangeComponent.h"
#include "DynamicScene.h"

void app::test::SceneChangeComponent::Begin()
{
	updateCommand.Bind(std::bind(&SceneChangeComponent::Update, this));
}

void app::test::SceneChangeComponent::Update()
{
	//スペースキーが押されたら
	if (SInput::Instance().GetKeyDown(Key::SPACE))
	{
		//シーンがメモリ上に存在しなければ
		if (scene.isNull())
		{
			//シーンをスタンバイ状態にする
			scene = DynamicScene::StandbyScene();
		}
		else
		{
			//シーンが実体化されていたら
			if (scene->IsActivate())
			{
				//シーンを削除する
				scene->DeActivate();
				scene = nullptr;
			}
			else
			{
				//シーンの読み込みが完了していたら
				if (scene->StandbyThisScene())
				{
					//シーンを実体化させる
					scene->Activate();
				}
				else
				{
					sf::debug::Debug::LogWarning("シーン読み込みが完了していません！");
				}
			}
		}
	}
}

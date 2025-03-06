#pragma once
#include "Component.h"
#include "Singleton.h"
#include "DirectX11.h"
namespace sf
{
	//カメラコンポーネント
	class Camera :public Component
	{
	public:
		void Begin()override;

		/// <summary>
		/// ビュー変換行列
		/// </summary>
		/// <returns></returns>
		DirectX::XMMATRIX GetViewMatrix()const;

		/// <summary>
		/// プロジェクション行列
		/// </summary>
		/// <returns></returns>
		DirectX::XMMATRIX GetMatrixProj()const;

		Vector3 WorldToScreen(Vector3 p)const;

		sf::SafePtr<Camera> Instance() { return main; }

		static void SetGPU();

		void SetGPUShadow()const;

	private:
		void Update();

	public:
		static Camera* main;

		static Camera* shadow;

		float fov = 90;

		float nearClip = 0.1f;

		float farClip = 1000.0f;

	private:
		command::Command<7> command;

		static VP vp;
	};
}
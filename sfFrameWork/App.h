#pragma once
#pragma once
#include "sf.h"
#include "Scene.h"
#include "Time.h"
#include "SInput.h"
#include "SkyBox.h"

namespace app
{
	//�Q�[���̃A�v���P�[�V����
	class Application
	{
	public:
		Application();
		~Application();

		/// <summary>
		/// ���C���A�v���P�[�V����
		/// </summary>
		/// <returns></returns>
		static Application* GetMain() { return main; }

		/// <summary>
		/// �A�v���P�[�V�����̎��s
		/// </summary>
		void Run();

		/// <summary>
		/// �A�N�e�B�x�[�g�̃V�[����ǉ�
		/// </summary>
		/// <param name="scene"></param>
		void ActivateScene(sf::IScene* scene);

		/// <summary>
		/// �A�N�e�B�x�[�g�̃V�[�����폜
		/// </summary>
		/// <param name="scene"></param>
		void DeActivateScene(const sf::IScene* scene);

		/// <summary>
		/// �A�v���P�[�V�����̏I��
		/// </summary>
		void Exit();

	private:
		void Init();
		void UnInit();
		void Loop();

		void DrawShadow();

		bool OnGUI();

		bool CreateGameWindow();

		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

	public:
		sf::jobsystem::JobSystem jobSystem;

		sf::del::VDelegate OnApplicationExit;

		static int width;
		static int height;

	private:
		static Application* main;

		float fps[60]{ 
			60,60,60,60,60,60,60,60,60,60,
			60,60,60,60,60,60,60,60,60,60,
			60,60,60,60,60,60,60,60,60,60,
			60,60,60,60,60,60,60,60,60,60,
			60,60,60,60,60,60,60,60,60,60,
			60,60,60,60,60,60,60,60,60,60,
		};

		//�Q�[���E�B���h�E
		sf::window::Window gameWindow;

		SkyBox skybox;

		//�A�N�e�B�u�V�[��
		std::vector<sf::IScene*> activeScene;

		std::mutex scenesMtx;

		bool exit = false;

		sf::file::TextFile fpsFile = sf::file::TextFile("log\\fps.txt");
	};
}
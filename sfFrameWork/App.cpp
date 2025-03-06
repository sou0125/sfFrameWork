#include "App.h"
#include "DirectX11.h"
#include "ResidentScene.h"

app::Application* app::Application::main = nullptr;

int app::Application::width = 1920;
int app::Application::height = 1080;

app::Application::Application()
{
	sf::debug::Debug::Log("�A�v���P�[�V�����J�n");

	if (main == nullptr)
	{
		main = this;
	}
	else
	{
		sf::debug::Debug::LogError("�����̃A�v���P�[�V�����������ɑ��݂��Ă��܂�");
	}

	sf::debug::Debug::WriteLogFile();

	OnApplicationExit += sf::IScene::DestroyFromOnApplicaitonExit;

	fpsFile.Clean();
}

app::Application::~Application()
{
	if (main == this)
	{
		main = nullptr;
	}

	sf::debug::Debug::Log("�A�v���P�[�V�����I��");

	exit = false;
}

void app::Application::Run()
{
	try
	{
		sf::debug::Debug::Log("�A�v���P�[�V�����̏��������J�n���܂�");
		Init();
	}
	catch (const std::exception& log)
	{

		sf::debug::Debug::LogError(log.what());
		sf::debug::Debug::LogError("�Q�[���������I�����܂�");

		return;
	}


	Loop();

	UnInit();
}

void app::Application::ActivateScene(sf::IScene* scene)
{
	{
		std::lock_guard<std::mutex> lock(scenesMtx);
		activeScene.push_back(scene);
		sf::debug::Debug::LogEngine("�V�[�����A�N�e�B�x�[�g����܂���:" + std::string(typeid(*scene).name()));
	}
}

void app::Application::DeActivateScene(const sf::IScene* scene)
{
	{
		std::lock_guard<std::mutex> lock(scenesMtx);
		auto it = std::find(activeScene.begin(), activeScene.end(), scene);

		if (it != activeScene.end())
		{
			activeScene.erase(it);
		}
	}
}

void app::Application::Exit()
{
	exit = true;
}

void app::Application::Init()
{
	//�E�B���h�E�쐬
	CreateGameWindow();

	//�T�E���h���\�[�X�̏�����
	sf::sound::SoundResource::Init();

	//���͂̏�����
	SInput::Init();

	//���Ԃ̏�����
	sf::Time::Init();

	//DirectX�̏�����
	sf::dx::DirectX11::Init();
	sf::dx::DirectX11::Instance()->Create(gameWindow.hwnd);

#ifdef USEGUI
	//GUI�̏�����
	sf::gui::GUI::Init(
		gameWindow.hwnd,
		sf::dx::DirectX11::Instance()->GetMainDevice().GetDevice(),
		sf::dx::DirectX11::Instance()->GetMainDevice().GetContext()
	);
#endif

	//�X�J�C�{�b�N�X�̏�����
	skybox.Init();

	//ResidentScene��ǂݍ���(��ɑ��݂���V�[��)
	auto scene = ResidentScene::StandbyScene();

	while (1)
	{
		//ResidentScene�̓ǂݍ��݂�҂�
		if (ResidentScene::Standby())
		{
			break;
		}
	}

	//ResidentScene���A�N�e�B�x�[�g��Ԃɂ���
	scene->Activate();
}

void app::Application::UnInit()
{
	for (auto& i : activeScene) {
		delete i;
	}

	OnApplicationExit();

#ifdef USEGUI
	sf::gui::GUI::UnInit();
#endif

	sf::sound::SoundResource::UnInit();
	sf::dx::DirectX11::UnInit();

	SInput::UnInit();
}

void app::Application::Loop()
{
	//sf::Time::SetFPS(0);
	//sf::Time::SetFPS(120);

	sf::debug::Debug::Log("�Q�[�����[�v�ł�");
	MSG msg{};
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
		{
			if (msg.message == WM_QUIT) { break; }

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (sf::Time::Update())
			{
				//���͂̍X�V
				SInput::Instance().Update();

				//DirectX11�̎擾
				sf::dx::DirectX11* dx11 = sf::dx::DirectX11::Instance();

				//GPU�ɃV�X�e�����𑗐M����
				static float t = 0.0f;
				t += sf::Time::DeltaTime();
				System sys;
				sys.time.x = t;
				sys.screenSize = DirectX::XMFLOAT2A(1920, 1080);
				dx11->systemBuffer.SetGPU(sys, dx11->GetMainDevice());

#ifdef USEGUI
				//GUI�`��
				sf::gui::GUI::Begin();

				const float l = 10;
				sf::debug::Debug::DrawLine(Vector3(-l, 0, 0), Vector3(l, 0, 0), DirectX::XMFLOAT4(1, 0, 0, 1));
				sf::debug::Debug::DrawLine(Vector3(0, -l, 0), Vector3(0, l, 0), DirectX::XMFLOAT4(0, 1, 0, 1));
				sf::debug::Debug::DrawLine(Vector3(0, 0, -l), Vector3(0, 0, l), DirectX::XMFLOAT4(0, 0, 1, 1));
#endif

				//RTV�̓h��Ԃ�
				dx11->SetViewPort(1920, 1080);

				//�S�R�}���h�̎���
				sf::command::ICommand::CallAll();

				//�e�̕`��
				DrawShadow();

				//�J��������GPU�ɓ]��
				sf::Camera::SetGPU();

				//���̃����_�����O�o�b�t�@�ɐ؂�ւ�
				dx11->SetNextRenderingDoubleBuffer3D();

				//�X�J�C�{�b�N�X�`��ݒ�
				//dx11->SetRenderingDoubleBuffer3DSkyBox();

				//�X�J�C�{�b�N�X�`��
				//skybox.Draw();

				//3D�`��J�n
				dx11->SetRenderingDoubleBuffer3D();

				//�V���h�E�}�b�v��GPU�ɓ]��
				ID3D11ShaderResourceView* srv = nullptr;
				dx11->GetMainDevice().GetContext()->PSSetShaderResources(3, 1, &srv);
				dx11->shadowRTV.SetTexture(dx11->GetMainDevice(), 3);

				//���b�V���̕`��
				sf::Mesh::DrawAll();

				//�f�o�b�O���C���̕`��
				sf::debug::Debug::DrawLog();

				//2D�`��J�n
				dx11->SetRenderingDoubleBuffer2D();

				//UI�`��
				sf::ui::Canvas::DrawCanvasies();

				//�I���X�N���[���`��J�n
				dx11->OnScreenRendering();

				bool exitFg = false;
#ifdef USEGUI
				exitFg = OnGUI();
#endif
				//�_�u���o�b�t�@�؂�ւ�
				dx11->Flip();

				//�A�N�^�[�̔j��
				sf::Actor::DestroyActors();

				//�V�[���̔j��
				sf::IScene::DestroyScenes();

				if (exitFg)break;

				if (exit)break;

				double fps = sf::Time::GetFPS();
				std::string strFps = std::to_string(fps);

				fpsFile.Write({ strFps });

				if (fps < 30)
				{
					sf::debug::Debug::LogEngine("FPS���ቺ���Ă��܂�:" + strFps);
				}
			}
		}
	}
}

void app::Application::DrawShadow()
{
	//DX11�̎擾
	sf::dx::DirectX11* dx11 = sf::dx::DirectX11::Instance();

	//�h��Ԃ�
	float color[] = { 0,0,0,1 };
	dx11->GetMainDevice().GetContext()->ClearRenderTargetView(dx11->shadowRTV.GetRTV(), color);
	ID3D11RenderTargetView* rtv[]
	{
		dx11->shadowRTV.GetRTV(),
	};

	//RTV,DSV��GPU�ɃZ�b�g
	dx11->GetMainDevice().GetContext()->ClearDepthStencilView(dx11->depth, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dx11->GetMainDevice().GetContext()->OMSetRenderTargets(ARRAYSIZE(rtv), rtv, dx11->depth);

	//�e�p�s�N�Z���V�F�[�_�[��GPU�ɃZ�b�g
	dx11->psShadow.SetGPU(dx11->GetMainDevice());

	//�J��������GPU�ɓ]��
	sf::Camera::shadow->SetGPUShadow();

	{
		//�s�N�Z���V�F�[�_�[�̐؂�ւ������b�N
		sf::dx::shader::PixelShader::Lock();

		//�V���h�E�}�b�v�ɕ`��
		sf::Mesh::DrawShadowAll();

		//�s�N�Z���V�F�[�_�[�̐؂�ւ����ă��b�N
		sf::dx::shader::PixelShader::UnLock();
	}

	//ImGui::Begin("Shadow");

	//ImGui::Image(ImTextureID(dx11->shadowRTV.GetSRV()), ImVec2(400, 400));

	//ImGui::End();
}

bool app::Application::OnGUI()
{
	//DirectX11�̎擾
	sf::dx::DirectX11* dx11 = sf::dx::DirectX11::Instance();


	sf::debug::Debug::TraceLog();

	for (auto& i : activeScene) {
		i->OnGUI();
	}

	ImGui::Begin("GBuffer");

	ImVec2 s;
	s.x = 200;
	s.y = 200;

	ImGui::Text(sf::ConvertToUTF8("�����_�����O�o�b�t�@").c_str());

	ImGui::Text(sf::ConvertToUTF8("3D�x�[�X�J���[").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->rb3d.Get().GetBaseColorRTV().GetSRV()),
		s);

	ImGui::Text(sf::ConvertToUTF8("3D�@��").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->rb3d.Get().GetNormalRTV().GetSRV()),
		s);
	ImGui::Text(sf::ConvertToUTF8("3D�A���t�@�[�x").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->rb3d.Get().GetAlphaRTV().GetSRV()),
		s);
	ImGui::Text(sf::ConvertToUTF8("�P�x").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->rb3d.Get().GetLuminanceRTV().GetSRV()),
		s);
	ImGui::Text(sf::ConvertToUTF8("DownX").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->downX.GetSRV()),
		s);
	ImGui::Text(sf::ConvertToUTF8("DownY").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->downY.GetSRV()),
		s);
	ImGui::Text(sf::ConvertToUTF8("2D�x�[�X�J���[").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->rb2d.GetBaseColorRTV().GetSRV()),
		s);
	ImGui::Text(sf::ConvertToUTF8("2D�A���t�@�l").c_str());
	ImGui::Image(
		(ImTextureID)(dx11->rb2d.GetAlphaRTV().GetSRV()),
		s);

	ImGui::End();

	ImGui::Begin("System");

	bool exitFg = false;
	if (ImGui::Button("Exit"))
	{
		int i = MessageBox(nullptr, "���s���~���܂����H", "Exit", MB_YESNO);
		if (i == IDYES)
		{
			exitFg = true;
		}
	}

	if (ImGui::Button(sf::ConvertToUTF8("���I�R���p�C��").c_str()))
	{
		//���I�R���p�C�����s���ɂ�F5�������ĉ�����
		__debugbreak();  // Visual Studio�̃f�o�b�K�Œ�~���܂�
	}

	float c = 0;
	for (int i = 60 - 1; i > 0; i--)
	{
		fps[i] = fps[i - 1];
		c += fps[i];
	}
	fps[0] = sf::Time::GetFPS();
	c += fps[0];
	c /= 60.0f;
	ImGui::Text(sf::ConvertToUTF8(std::string("���ۂ�FPS:" + std::to_string(sf::Time::GetFPS()))).c_str());
	ImGui::Text(sf::ConvertToUTF8(std::string("����FPS:" + std::to_string(c))).c_str());

	ImGui::End();

	sf::gui::GUI::End();

	return exitFg || exit;
}

bool app::Application::CreateGameWindow()
{
	gameWindow.wc.lpfnWndProc = WndProc;
	gameWindow.windowName = "Window1";
	gameWindow.className = "Class1";

	return gameWindow.Create(WS_POPUP);
	return gameWindow.Create();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler
(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT app::Application::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp)) {
		return true;
	}

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			//��������̃L�[�������ꂽ��
		SInput::Instance().SetKeyDown(static_cast<int>(wp));
		break;

	case WM_KEYUP:				//��������̃L�[�������ꂽ��
		SInput::Instance().SetKeyUp(static_cast<int>(wp));
		break;
	case WM_LBUTTONDOWN:
		SInput::Instance().SetMouseDown(0);
		break;
	case WM_RBUTTONDOWN:
		SInput::Instance().SetMouseDown(1);
		break;
	case WM_LBUTTONUP:
		SInput::Instance().SetMouseUp(0);
		break;
	case WM_RBUTTONUP:
		SInput::Instance().SetMouseUp(1);
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

#include "Window.h"
#include "sf.h"

sf::window::Window::Window()
{
	hInst = GetModuleHandle(nullptr);

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//wc.lpfnWndProc = WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);
}

sf::window::Window::~Window()
{
	UnregisterClass(wc.lpszClassName, hInst);
}

bool sf::window::Window::Create(int width, int height, int style)
{
	wc.lpszClassName = className.c_str();

	//�E�B���h�E�̓o�^.
	if (!RegisterClassEx(&wc))
	{
		throw std::runtime_error("�E�B���h�E�̓o�^�Ɏ��s���܂���");
		return false;
	}

	RECT rc = {};
	rc.right = static_cast<LONG>(width);
	rc.bottom = static_cast<LONG>(height);

	AdjustWindowRect(&rc, style, FALSE);

	// �E�B���h�E�𐶐�.
	hwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		windowName.c_str(),
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInst,
		nullptr);

	if (hwnd == nullptr)
	{
		throw std::runtime_error("�E�B���h�E�̍쐬�Ɏ��s���܂���");
		return false;
	}

	// �E�B���h�E��\��.
	ShowWindow(hwnd, SW_SHOWNORMAL);

	// �E�B���h�E���X�V.
	UpdateWindow(hwnd);

	debug::Debug::LogSafety("�E�B���h�E�̍쐬�ɐ������܂���");

	return true;
}

bool sf::window::Window::Create(int style)
{
	HWND desctopWindow = GetDesktopWindow();

	RECT rect;
	GetClientRect(desctopWindow, &rect);

	int deskTopw = rect.right - rect.left;
	int deskToph = rect.bottom - rect.top;

	return Create(deskTopw, deskToph, style);
}

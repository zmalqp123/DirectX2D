#include "stdafx.h"
#include "Game.h"

// ���־� ��Ʃ����� ���� ���ø��� �ٸ� �߰����� ������ ���� �����ϱ� ����� ���� �����ϰ� �ۼ���.

// ������ ���ν��� �Լ� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ������Ʈ �Ӽ� -> ��Ŀ -> �ý��� -> ���� �ý��� -> Windows�� ����
// ������ �Լ� ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ������ Ŭ���� ����ü �ʱ�ȭ
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// ������ ���ν��� �Լ�
	wc.hInstance = hInstance;   // �ν��Ͻ� �ڵ�
	// NULL�� ����ϸ� ���� ���� ���� ���α׷��� �ν��Ͻ� �ڵ��� ����ϰ� �˴ϴ�.�� ��° ���ڴ� �ε��� Ŀ���� ID�Դϴ�.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"BasicWindowClass";

	// ������ Ŭ���� ���
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"������ Ŭ���� ��� ����", L"����", MB_OK | MB_ICONERROR);
		return 1;
	}

	// ���ϴ� ũ�Ⱑ �����Ǿ� ����
	SIZE clientSize = { 1920, 1280 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// ������ ����
	HWND hwnd = CreateWindowEx(
		0,
		L"BasicWindowClass",
		L"������ ������",
		WS_OVERLAPPEDWINDOW,	// OR�������� ���յ� ������â ��Ÿ��
		0,0,	// ������ġ
		clientRect.right-clientRect.left,  clientRect.bottom - clientRect.top , // �ʺ�, ����
		NULL, NULL, hInstance, NULL
	);

	if (!hwnd)
	{
		MessageBox(NULL, L"������ ���� ����", L"����", MB_OK | MB_ICONERROR);
		return 1;
	}

	// ������ ǥ��
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	bool bUseConsole=false;
	if (bUseConsole)
	{
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	}	

	

	Game::Init(hwnd, clientSize.cx, clientSize.cy);

	// ��Ⱑ ���� �޼��� ����
	MSG msg;
	while (true)
	{
		// �޽����� ������ ó��, ������ �ٷ� ���� ������ �̵�
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUIT �޽��� Ȯ��
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ���� ����				
			Game::Update();
			Game::Render();
		}
	}

	Game::Uninit();
	
	if (bUseConsole)
	{
		FreeConsole();
	}

	return static_cast<int>(msg.wParam);
}

// ������ ���ν��� �Լ� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

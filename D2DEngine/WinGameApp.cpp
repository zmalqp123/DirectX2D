#include "pch.h"
#include "WinGameApp.h"
#include <cmath>
#include "InputManager.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WinGameApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	// 공통으로 사용하는 윈도우 설정,생성부분을 작성한다.

	// Direct2D초기화를 작성한다.
    
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = hInstance;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wcex.lpszClassName = L"D2DDemoApp";

    RegisterClassEx(&wcex);

    hInst = hInstance;
    hwnd = CreateWindow(
        L"D2DDemoApp",
        L"Direct2D demo application",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        NULL,
        NULL,
        hInstance,
        this);

    if (hwnd)
    {
        float dpi = GetDpiForWindow(hwnd);

        SetWindowPos(
            hwnd,
            NULL,
            NULL,
            NULL,
            static_cast<int>(ceil(1280.f * dpi / 96.f)),
            static_cast<int>(ceil(720.f * dpi / 96.f)),
            SWP_NOMOVE);

        D2DRenderer::getIncetance().InitDirect2D(hwnd);
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);
    }

    InputManager::GetInstance().InitInput(hwnd);
    deltaTime.InitTime();
}

void WinGameApp::Run()
{
	// 공통으로 사용하는 윈도우 게임 루프를 작성한다.
    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg = { };
    bool bQuit = false;

    while (!bQuit) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                bQuit = true;
            }
            else if (msg.message == WM_KEYDOWN || msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN)
            {
                InputManager::GetInstance().KeyDown(msg.wParam);
            }
            else if (msg.message == WM_KEYUP || msg.message == WM_LBUTTONUP || msg.message == WM_RBUTTONUP)
            {
                InputManager::GetInstance().KeyUp(msg.wParam);
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        InputManager::GetInstance().UpdateMouse();
        deltaTime.UpdateTime();
        
        // 이걸 사용하면 화면 크기를 마음대로 변경 가능.
       /* if (GetKeyState(0x44) < 0) {
            float dpi = GetDpiForWindow(hwnd);
            SetWindowPos(
                hwnd,
                NULL,
                NULL,
                NULL,
                static_cast<int>(ceil(1920.f * dpi / 96.f)),
                static_cast<int>(ceil(1080.f * dpi / 96.f)),
                SWP_NOMOVE);
        }*/

        static ULONGLONG elapsedTime;

        elapsedTime += deltaTime.GetDeltaTime();

        while (elapsedTime >= 20) //0.02초
        {
            //++m_FixedUpdateCount;

            elapsedTime -= 20;
        }

        Update(deltaTime.GetDeltaTime());
        D2DRenderer::getIncetance().BeginDraw();
        D2DRenderer::getIncetance().Clear(D2D1::ColorF(D2D1::ColorF::Coral));
        Render(&D2DRenderer::getIncetance());
        D2DRenderer::getIncetance().EndDraw();

        InputManager::GetInstance().ResetInput();
    }
}
void WinGameApp::FixedUpdate()
{
}
void WinGameApp::Update(float delatTime) {
    //temp += deltaTime.GetDeltaTime() + 2.f;
}

void WinGameApp::LateUpdate()
{
}

void WinGameApp::Render(D2DRenderer* _render)
{
}

void WinGameApp::Uninitialize()
{
	// Direct2D 해제를 호출한다.
    D2DRenderer::getIncetance().UnInitDirect2D();

    CoUninitialize();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

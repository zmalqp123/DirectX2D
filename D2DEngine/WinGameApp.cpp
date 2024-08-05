#include "pch.h"
#include "WinGameApp.h"
#include <cmath>
#include "InputManager.h"
#include "PublicData.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WinGameApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	// �������� ����ϴ� ������ ����,�����κ��� �ۼ��Ѵ�.

	// Direct2D�ʱ�ȭ�� �ۼ��Ѵ�.
    
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
    //
    if (hwnd)
    {
        float dpi = GetDpiForWindow(hwnd);
        float sizeX = static_cast<int>(ceil(1280.f * dpi / 96.f));
        float sizeY = static_cast<int>(ceil(720.f * dpi / 96.f));
        RECT rect = { 0, 0, sizeX, sizeY};

        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL); // �ÿ���� �����ֽ� �ڵ� Ŭ���̾�Ʈ ��ǥ�� ����
        SetWindowPos(
            hwnd,
            NULL,
            NULL,
            NULL,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOMOVE);

        D2DRenderer::getIncetance().InitDirect2D(hwnd);
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);
        
        PublicData::GetInstance().SetHWND(hwnd);
        PublicData::GetInstance().SetScreenSize(Vector2( sizeX, sizeY ));
    }


    InputManager::GetInstance().InitInput(hwnd);
    deltaTime.InitTime();

}
int FPS = 0;
void WinGameApp::Run()
{
	// �������� ����ϴ� ������ ���� ������ �ۼ��Ѵ�.
    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg = { };
    bool bQuit = false;

    while (!bQuit) {
        bool wheelMoved = false;
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
            else if (msg.message == WM_MOUSEWHEEL) {
                InputManager::GetInstance().MouseWheel(GET_WHEEL_DELTA_WPARAM(msg.wParam));
                wheelMoved = true;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        InputManager::GetInstance().UpdateMouse(wheelMoved);
        deltaTime.UpdateTime();
        
        // �̰� ����ϸ� ȭ�� ũ�⸦ ������� ���� ����.
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

        while (elapsedTime >= 20) //0.02��
        {
            //++m_FixedUpdateCount;

            elapsedTime -= 20;
        }

        Update(deltaTime.GetDeltaTime());
        D2DRenderer::getIncetance().BeginDraw();
        D2DRenderer::getIncetance().Clear(D2D1::ColorF(D2D1::ColorF::Black));
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
   /* _render->getRenderTarget().SetTransform(D2D1::Matrix3x2F::Identity());
    auto str = std::to_wstring(deltaTime.GetFPS()); 
    str += L", ";
    str += std::to_wstring(_render->GetUsedVRAM());
    _render->DrawStringText(str.c_str());*/
}

void WinGameApp::Uninitialize()
{
	// Direct2D ������ ȣ���Ѵ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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

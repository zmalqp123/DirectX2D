#pragma once
#include "Windows.h"
#include "DeltaTime.h"
#include "D2DRenderer.h"

#include <d2d1.h>
//#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib") // Direct2D ���̺귯�� ��ũ

class WinGameApp
{
private:
	HINSTANCE hInst;
	HWND hwnd;
	//D2DRenderer& render;

	DeltaTime deltaTime;
public:

	// �ڽ� Ŭ������ ������ �����ϵ��� virtual keyword �� ���δ�.
	virtual void Initialize(HINSTANCE hInstance, int nCmdShow);
	void Run();
	virtual void FixedUpdate();
	virtual void Update(float deltaTime);
	virtual void LateUpdate();
	virtual void Render(D2DRenderer* _render);
	virtual void Uninitialize();
};


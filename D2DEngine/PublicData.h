#pragma once
#include "D2DRenderer.h"
#include "Vector.h"
// Hwnd, ������ ȭ�� ũ�� ���� ������ ����.
class PublicData
{
private:
	HWND hWnd;
	Vector2 screenSize;

public:
	static PublicData& GetInstance() {
		static PublicData instance;
		return instance;
	}

	void SetHWND(HWND _h) { hWnd = _h; }
	void SetScreenSize(Vector2 _s) { screenSize = _s; }


	HWND GetHWND() { return hWnd; }
	Vector2 GetScreenSize() { return screenSize; }
};


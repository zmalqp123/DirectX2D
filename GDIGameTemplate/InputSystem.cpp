#include "stdafx.h"
#include "InputSystem.h"

namespace Input
{
	// Ű���� �Է� ���� ����
	#define KEYBOARD_MAX 256		// ��ü ���� Ű�� ��  https://learn.microsoft.com/ko-kr/windows/win32/inputdev/virtual-key-codes
	BYTE g_byKeyPrev[KEYBOARD_MAX];		// ���� Ű�� ����
	BYTE g_byKeyCurr[KEYBOARD_MAX];		// ���� Ű�� ����
	BYTE g_byKeyTurnDn[KEYBOARD_MAX];	// Down�� Ű�� ����
	BYTE g_byKeyTurnUp[KEYBOARD_MAX];   // Up �� Ű�� ����

	HWND hWnd;
	int nWidth;
	int nHeight;
	
	POINT mouseClient;

	void Update()
	{
		GetCursorPos(&mouseClient);
		ScreenToClient(hWnd, &mouseClient);
	
		// Ű���� ���� ����
		bool ret = GetKeyboardState((PBYTE)&g_byKeyCurr);	// 0x80 : ����, 0x00 : ������ ����
		
		for (int i = 0; i < KEYBOARD_MAX; i++)
		{
			g_byKeyTurnUp[i] = (g_byKeyPrev[i] ^ g_byKeyCurr[i]) & g_byKeyPrev[i];
			g_byKeyTurnDn[i] = (g_byKeyPrev[i] ^ g_byKeyCurr[i]) & g_byKeyCurr[i];
		}
		memcpy(&g_byKeyPrev, &g_byKeyCurr, KEYBOARD_MAX);
	}

	void InitInput(HWND hWindow,int width,int height)
	{
		hWnd = hWindow;
		nWidth = width;
		nHeight = height;

		mouseClient.x = nWidth / 2;
		mouseClient.x = nHeight / 2;
		SetCursorPos(mouseClient.x, mouseClient.y);
	}

	void ReleaseInput()
	{

	}

	BOOL IsTurnDn(BYTE vk)
	{
		if (g_byKeyTurnDn[vk] & 0x80)
			return TRUE;

		return FALSE;
	}

	BOOL IsTurnUp(BYTE vk)
	{
		if (g_byKeyTurnUp[vk] & 0x80)
			return TRUE;

		return FALSE;

	}

	BOOL IsCurrDn(BYTE vk)
	{
		if (g_byKeyCurr[vk] & 0x80)
			return TRUE;

		return FALSE;
	}

	BOOL IsCurrUp(BYTE vk)
	{
		if (g_byKeyCurr[vk] & 0x80)
			return FALSE;

		return TRUE;

	}

	POINT GetMouseClient()
	{
		return mouseClient;
	}

}
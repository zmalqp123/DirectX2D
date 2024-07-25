#include "pch.h"
#include "InputManager.h"

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::InitInput(HWND _hWnd)
{
	hWnd = _hWnd;
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
		isKey[i] = false;
	}
	memset(buffer, '\0', 255);
	InitMouse();
}

void InputManager::InitMouse()
{
	curMouse.wheel = 0;

	curMouse.left = false;
	curMouse.right = false;
	curMouse.middle = false;

	prevMouse = curMouse;
}

void InputManager::ResetInput()
{
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
	}
}

void InputManager::KeyDown(unsigned int key)
{
	isKeyDown[key] = true;
	isKey[key] = true;
}

void InputManager::KeyUp(unsigned int key)
{
	isKeyUp[key] = true;
	isKey[key] = false;
}

bool InputManager::IsKeyDown(unsigned int key)
{
	return isKeyDown[key];
}

bool InputManager::IsKeyUp(unsigned int key)
{
	return isKeyUp[key];
}

bool InputManager::IsKey(unsigned int key)
{
	return isKey[key];
}

void InputManager::UpdateMouse()
{
	prevMouse = curMouse;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	curMouse.x = pt.x;
	curMouse.y = pt.y;
	curMouse.wheel = 0;

	curMouse.left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	curMouse.right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
	curMouse.middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
}

bool InputManager::IsSame(const MouseState& a, const MouseState& b)
{
	return a.x == b.x && a.y == b.y && a.wheel == b.wheel && a.left == b.left && a.right == b.right && a.middle == b.middle;
}

const InputManager::MouseState& InputManager::GetMouseState()
{
	return curMouse;
}

const InputManager::MouseState& InputManager::GetPrevMouseState()
{
	return prevMouse;
}

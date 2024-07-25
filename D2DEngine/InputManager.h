#pragma once
class InputManager
{
private:
	InputManager() {};
	~InputManager();
public:
	static InputManager& GetInstance();

	void InitInput(HWND _hWnd);
	void InitMouse();
	void ResetInput();
	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	bool IsKeyDown(unsigned int key);
	bool IsKeyUp(unsigned int key);
	bool IsKey(unsigned int key);

	struct MouseState
	{
		MouseState()
		{
			x = 0;
			y = 0;
			wheel = 0;
			left = false;
			right = false;
			middle = false;
		}

		int x;
		int y;
		int wheel;
		bool left;
		bool right;
		bool middle;
	};

	void UpdateMouse();

	bool IsSame(const MouseState& a, const MouseState& b);

	const MouseState& GetMouseState();
	const MouseState& GetPrevMouseState();
private:
	HWND hWnd;

	bool isKeyDown[256];
	bool isKeyUp[256];
	bool isKey[256];

	MouseState curMouse;
	MouseState prevMouse;

	TCHAR buffer[255] = { 0 };
	int length = 0;
	bool isInputKey = false;
};


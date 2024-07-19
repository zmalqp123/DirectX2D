#pragma once
#include "../D2DEngine/WinGameApp.h"
//#include "Windows.h"
class Scene;
class FSMDemo : public WinGameApp
{
public:

	Scene* scene;
	//  virtual �� ����ص� ������
	// override�� keyword�� ����ϹǷν� �����Լ� "������" ��°��� Ȯ�����Ѵ�.
	// �θ� Ŭ������ �Լ��� virtual �� �ƴϸ� ������ ����.
	virtual void Initialize(HINSTANCE hInstance, int nCmdShow);

	virtual void Run();

	virtual void Update(float deltaTime);

	virtual void Render(D2DRenderer* _render);

	virtual void Uninitialize();
};

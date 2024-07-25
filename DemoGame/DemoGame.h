#pragma once
#include "../D2DEngine/WinGameApp.h"
//#include "Windows.h"

class TestObject;
class Scene;
class DemoGame : public WinGameApp
{
public:
	Scene* scene;
	TestObject* testObj[3];
	//  virtual �� ����ص� ������
	// override�� keyword�� ����ϹǷν� �����Լ� "������" ��°��� Ȯ�����Ѵ�.
	// �θ� Ŭ������ �Լ��� virtual �� �ƴϸ� ������ ����.
	virtual void Initialize(HINSTANCE hInstance, int nCmdShow) override;

	virtual void Run() override;

	virtual void Update(float deltaTime) override;

	virtual void Render(D2DRenderer* _render) override;

	virtual void Uninitialize() override;
};

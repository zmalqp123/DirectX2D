#pragma once
#include "../D2DEngine/WinGameApp.h"
class CullingCamera : public WinGameApp
{
public:
	//  virtual �� ����ص� ������
	// override�� keyword�� ����ϹǷν� �����Լ� "������" ��°��� Ȯ�����Ѵ�.
	// �θ� Ŭ������ �Լ��� virtual �� �ƴϸ� ������ ����.
	virtual void Initialize(HINSTANCE hInstance, int nCmdShow) override;

	virtual void Run() override;

	virtual void Update(float deltaTime) override;

	virtual void Render(D2DRenderer* _render) override;

	virtual void Uninitialize() override;
};

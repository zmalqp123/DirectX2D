#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
class Camera;
class PlayerController : public Component, public IColliderNotify
{
public:
	Camera* cam;
	GameObject* timerObj;
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat);
	bool isDodgeRoll = false;

	// IColliderNotify��(��) ���� ��ӵ�
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	// IColliderNotify��(��) ���� ��ӵ�
	void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};


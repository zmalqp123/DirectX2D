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

	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	// IColliderNotify을(를) 통해 상속됨
	void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};


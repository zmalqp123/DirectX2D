#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
class Camera;
class PlayerController : public Component, public IColliderNotify
{
public:
	Camera* cam;
	void virtual Update(float delta);

	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};


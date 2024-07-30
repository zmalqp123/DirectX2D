#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
class Camera;
class PlayerController : public Component, public IColliderNotify
{
public:
	Camera* cam;
	void virtual Update(float delta);

	// IColliderNotify��(��) ���� ��ӵ�
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};


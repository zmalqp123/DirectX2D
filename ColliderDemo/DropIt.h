#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
#include "../D2DEngine/Vector.h"
class Transform;
class Generator;
class DropIt : public Component, public IColliderNotify
{
public:
	Transform* target = nullptr;
	Vector2 direction = { 0.f, 0.f };
	Generator* gn = nullptr;
	float moveSpeed = 300.f;

	void virtual Init();
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat);

	void SetTarget(Transform* _target);

	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};


#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
#include "../D2DEngine/Vector.h"
class Transform;
class Generator;
class Bullet : public Component
{
public:
	Transform* target = nullptr;
	Vector2 direction = { 0.f, 0.f };
	Generator* gn = nullptr;
	float moveSpeed = 200.f;

	void virtual Init();
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat);

	void SetTarget(Transform* _target);
};


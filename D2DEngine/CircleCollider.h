#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
public:
	CircleCollider(CollisionType cType = BLOCK) {
		m_ColliderType = ColliderType::Circle;
		m_CollisionType = cType;
	}

	// Collider을(를) 통해 상속됨
	bool isCollide(Collider* collider) override;
};


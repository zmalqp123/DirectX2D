#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
public:
	CircleCollider(CollisionType cType = BLOCK) {
		m_ColliderType = ColliderType::Circle;
		m_CollisionType = cType;
	}

	// Collider��(��) ���� ��ӵ�
	bool isCollide(Collider* collider) override;
};


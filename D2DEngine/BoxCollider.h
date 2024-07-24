#pragma once
#include "Collider.h"
#include "AABB.h"
class BoxCollider : public Collider
{
private:
	AABB m_Collider;
	Vector2 offset;
public:
	BoxCollider(CollisionType cType = BLOCK) {
		m_ColliderType = ColliderType::Box;
		m_CollisionType = cType;

		//test
		m_Collider.m_Center = { 0.f, 50.f };
		m_Collider.m_Extent = { 50.f, 50.f };

		offset = { 0.f, 0.f };
	}
	// Collider을(를) 통해 상속됨
	bool isCollide(Collider* collider, Vector2& resolution) override;

	virtual void Render(D2D1_MATRIX_3X2_F cameraMat);

	void SetOffset(const Vector2& _offset);
	void SetCenter(const Vector2& _center);
	void SetExtent(const Vector2& _extent);
};


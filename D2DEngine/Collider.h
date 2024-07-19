#pragma once

#include "Component.h"
#include <set>
enum class ColliderType {
	None,
	Circle,
	Box
};
enum class CollisionType {
	None,
	Block,
	Overlap
};
#define BLOCK CollisionType::Block
#define OVERLAP CollisionType::Overlap
class Collider;
class IColliderNotify {
public:
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
};

class Collider : public Component
{
protected:
	ColliderType m_ColliderType = ColliderType::None;
	CollisionType m_CollisionType = CollisionType::None;

	std::set<Collider*> m_ColliderStateCurr;
	std::set<Collider*> m_ColliderStatePrev;
public:
	Collider() = default;
	virtual ~Collider() = default;

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }
	ColliderType GetColliderType() { return m_ColliderType; }

	void ClearAndBackupCollideState();

	bool IsEmptyCollideStateCurr() { return m_ColliderStateCurr.empty(); }

	void InsertCollideState(Collider* pColliderComponent) { m_ColliderStateCurr.insert(pColliderComponent); }
	void ProcessOverlap();
	void ProcessBlock(Collider* pOtherComponent);

	virtual bool isCollide(Collider* collider) = 0;

	virtual void Update(float deltaTime);
};


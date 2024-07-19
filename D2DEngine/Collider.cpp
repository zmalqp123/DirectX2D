#include "pch.h"
#include "Collider.h"
#include "GameObject.h"

void Collider::ClearAndBackupCollideState()
{
	m_ColliderStatePrev = std::move(m_ColliderStateCurr);
	m_ColliderStateCurr.clear();
}

void Collider::ProcessOverlap()
{
	//begin
	for (auto& pColliderComponent : m_ColliderStateCurr) {
		if (m_ColliderStatePrev.find(pColliderComponent) == m_ColliderStatePrev.end()) {
			for (auto c : gameObject->components) {
				if (auto notify = dynamic_cast<IColliderNotify*>(c)) {
					if (notify != nullptr) {
						notify->OnBeginOverlap(this, pColliderComponent);
					}
				}
			}
		}
	}

	//end
	for (auto& pColliderComponent : m_ColliderStatePrev) {
		if (m_ColliderStateCurr.find(pColliderComponent) == m_ColliderStateCurr.end()) {
			for (auto c : gameObject->components) {
				if (auto notify = dynamic_cast<IColliderNotify*>(c)) {
					if (notify != nullptr) {
						notify->OnEndOverlap(this, pColliderComponent);
					}
				}
			}
		}
	}
}

void Collider::ProcessBlock(Collider* pOtherComponent)
{
}

void Collider::Update(float deltaTime)
{
	
}

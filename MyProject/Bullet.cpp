#include "Bullet.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/Vector.h"
#include "Generator.h"

void Bullet::Init()
{
}

void Bullet::Update(float delta)
{
	if (target != nullptr) {
		gameObject->transform->m_RelativeLocation = gameObject->transform->m_RelativeLocation + (direction * delta * moveSpeed);

		if (gameObject->transform->m_RelativeLocation.x > 700.f || gameObject->transform->m_RelativeLocation.x < -700.f ||
			gameObject->transform->m_RelativeLocation.y > 420.f || gameObject->transform->m_RelativeLocation.y < -420.f) {
			gn->pools.push(this);
			SetTarget(nullptr);
			gameObject->SetActive(false);
		}
	}
}

void Bullet::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}

void Bullet::SetTarget(Transform* _target)
{
	if (_target == nullptr) {
		target = nullptr;
		direction = { 0.f, 0.f };
		return;
	}
	target = _target;
	Vector2 dir = (Vector2)target->m_RelativeLocation - (Vector2)gameObject->transform->m_RelativeLocation;
	dir.Normalize();
	direction = dir;
}

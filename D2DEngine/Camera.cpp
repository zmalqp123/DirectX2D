#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "InputManager.h"
Vector2 Camera::ScreenToWorldPosition(Vector2 position)
{
	//아직 미완.
	Vector2 mousePosition = {
		position.x * gameObject->transform->m_WorldTransform._11 + position.y * gameObject->transform->m_WorldTransform._21 + gameObject->transform->m_WorldTransform._31,
		position.x * gameObject->transform->m_WorldTransform._12 + position.y * gameObject->transform->m_WorldTransform._22 + gameObject->transform->m_WorldTransform._32
	};
	return mousePosition;
}

Vector2 Camera::WorldToScreenPosition(Vector2 position)
{
	return Vector2();
}

#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PublicData.h"

Vector2 Camera::ScreenToWorldPosition(Vector2 position)
{
	// 스크린좌표를 화면 중심을 기준으로 변경
	Vector2 screenSize = PublicData::GetInstance().GetScreenSize();
	position.x -= screenSize.x / 2.f;
	position.y -= screenSize.y / 2.f;
	

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

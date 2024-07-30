#include "PlayerIdle.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/InputManager.h"
#include <cmath>
void PlayerIdle::Enter()
{
	Vector2 dir = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition()) - fsm->gameObject->transform->m_RelativeLocation;
	dir.Normalize();
	float dot = Vector2::DotProduct({ 0.f, 1.f }, dir);
	float rad = std::acosf(dot);
	float deg = rad * (180.f / 3.14159f);
	float cross = Vector2::CrossProduct({ 0.f, 1.f }, dir);

	int animSet = -1;
	if (deg >= 0.f && deg < 30.f) {
		animSet = 3;
	}
	else if (deg >= 30.f && deg < 60.f) {
		animSet = 2;
	}
	else if (deg >= 60.f && deg < 135.f) {
		animSet = 1;
	}
	else {
		animSet = 0;
	}
	//fsm->gameObject->spriteAnim->SetAnimation(animSet, cross < 0 ? false : true);
	fsm->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(0, false);
}

void PlayerIdle::Update(float deltaTime)
{
	Vector2 dir = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition()) - fsm->gameObject->transform->m_RelativeLocation;
	dir.Normalize();
	float dot = Vector2::DotProduct({ 0.f, 1.f }, dir);
	float rad = std::acosf(dot);
	float deg = rad * (180.f / 3.14159f);
	float cross = Vector2::CrossProduct({ 0.f, 1.f }, dir);

	int animSet = -1;
	if (deg >= 0.f && deg < 30.f) {
		animSet = 3;
	}
	else if (deg >= 30.f && deg < 60.f) {
		animSet = 2;
	}
	else if (deg >= 60.f && deg < 135.f) {
		animSet = 1;
	}
	else {
		animSet = 0;
	}
	fsm->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(animSet, cross < 0 ? false : true, true);

	if(InputManager::GetInstance().IsKey(0x44)||
		InputManager::GetInstance().IsKey(0x41)||
		InputManager::GetInstance().IsKey(0x57)||
		InputManager::GetInstance().IsKey(0x53))
	{
		fsm->SetState("Walk");
	}
}

void PlayerIdle::Exit()
{
}

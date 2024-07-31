#include "PlayerDodgeRoll.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/Movement.h"
#include "PlayerWalk.h"
#include <cmath>
#include "../D2DEngine/BoxCollider.h"
#include "PlayerController.h"
void PlayerDodgeRoll::Enter()
{
	timer = maxTimer;

	Vector2 dir = pWalk->movement->m_direction;//cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition()) - fsm->gameObject->transform->m_RelativeLocation;
	dir.Normalize();
	float dot = Vector2::DotProduct({ 0.f, 1.f }, dir);
	float rad = std::acosf(dot);
	float deg = rad * (180.f / 3.14159f);
	float cross = Vector2::CrossProduct({ 0.f, 1.f }, dir);

	int animSet = -1;
	if (deg >= 0.f && deg < 30.f) {
		animSet = 11;
	}
	else if (deg >= 30.f && deg < 60.f) {
		animSet = 10;
	}
	else if (deg >= 60.f && deg < 135.f) {
		animSet = 9;
	}
	else {
		animSet = 8;
	}
	fsm->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(animSet, cross < 0 ? false : true);
	//fsm->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(8, false);

	fsm->gameObject->GetComponent<PlayerController>()->isDodgeRoll = true;
}

void PlayerDodgeRoll::Update(float deltaTime)
{
	timer -= deltaTime;

	movement->SetSpeed(300.f * timer);


	if (timer < 0.f) {
		if ((InputManager::GetInstance().IsKey(0x44) ||
			InputManager::GetInstance().IsKey(0x41) ||
			InputManager::GetInstance().IsKey(0x57) ||
			InputManager::GetInstance().IsKey(0x53)))
		{
			fsm->SetState("Walk");
		}

		fsm->SetState("Idle");
	}
}

void PlayerDodgeRoll::Exit()
{
	fsm->gameObject->GetComponent<PlayerController>()->isDodgeRoll = false;
	movement->SetSpeed(0.f);
}

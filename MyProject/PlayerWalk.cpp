#include "PlayerWalk.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/Movement.h"
#include <cmath>
PlayerWalk::PlayerWalk(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name)
{
	movement = _fsm->gameObject->CreateComponent<Movement>();
}
void PlayerWalk::Enter()
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
	fsm->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(4, false);

	movement->SetSpeed(200.f);
}

void PlayerWalk::Update(float deltaTime)
{
	Vector2 dir = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition()) - fsm->gameObject->transform->m_RelativeLocation;
	dir.Normalize();
	float dot = Vector2::DotProduct({ 0.f, 1.f }, dir);
	float rad = std::acosf(dot);
	float deg = rad * (180.f / 3.14159f);
	float cross = Vector2::CrossProduct({ 0.f, 1.f }, dir);

	int animSet = -1;
	if (deg >= 0.f && deg < 30.f) {
		animSet = 7;
	}
	else if (deg >= 30.f && deg < 60.f) {
		animSet = 6;
	}
	else if (deg >= 60.f && deg < 135.f) {
		animSet = 5;
	}
	else {
		animSet = 4;
	}
	fsm->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(animSet, cross < 0 ? false : true, true);

	Vector2 pos = {0.f, 0.f};
	if (GetKeyState(0x44) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * 100.f;
		pos.x += 1.f;
	}
	else if (GetKeyState(0x41) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * -100.f;
		pos.x += -1.f;
	}
	if (GetKeyState(0x57) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * 100.f;
		pos.y += 1.f;
	}
	else if (GetKeyState(0x53) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * -100.f;
		pos.y += -1.f;
	}
	if (pos.x == 0.f && pos.y == 0.f) {
		fsm->SetState("Idle");
	}
	if (GetKeyState(VK_SPACE) < 0) {
		fsm->SetState("DodgeRoll");
	}

	if (movement != nullptr)
	{
		pos.Normalize();
		movement->SetDirection(pos);
	}
}

void PlayerWalk::Exit()
{
	movement->SetSpeed(0.f);
}

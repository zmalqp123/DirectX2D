#include "PlayerMoving.h"
#include "framework.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/Movement.h"

#include <iostream>
PlayerMoving::PlayerMoving(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name)
{
	auto m = new Movement();
	movement = m;
	fsm->gameObject->AddComponent(m);
	m->SetOwner(fsm->gameObject);
}
void PlayerMoving::Enter()
{
	fsm->gameObject->spriteAnim->SetAnimation(1, false);
	movement->SetSpeed(200.f);
}
void PlayerMoving::Update(float deltaTime)
{
	float x = 0.f;
	float y = 0.f;
	if (GetKeyState(0x44) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * 100.f;
		x += 1.f;
	}
	else if (GetKeyState(0x41) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * -100.f;
		x += -1.f;
	}
	if (GetKeyState(0x57) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * 100.f;
		y += 1.f;
	}
	else if (GetKeyState(0x53) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * -100.f;
		y += -1.f;
	}
	if (x == 0.f && y == 0.f) {
		fsm->SetState("Idle");
	}

	if (movement != nullptr)
	{
		movement->SetDirection({ x,y });
	}
}

void PlayerMoving::Exit()
{
	movement->SetSpeed(0.f);
}

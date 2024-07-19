#include "EnemyTracking.h"
#include "framework.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/Movement.h"
EnemyTracking::EnemyTracking(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {
	auto m = new Movement();
	movement = m;
	fsm->gameObject->AddComponent(m);
	m->SetOwner(fsm->gameObject);
}
void EnemyTracking::Enter()
{
	fsm->gameObject->spriteAnim->SetAnimation(1, false);
	movement->SetSpeed(100.f);
}

void EnemyTracking::Update(float deltaTime)
{
	float disX = target->transform->m_RelativeLocation.x - fsm->gameObject->transform->m_RelativeLocation.x;
	float disY = target->transform->m_RelativeLocation.y - fsm->gameObject->transform->m_RelativeLocation.y;

	float dist = disX * disX + disY * disY;
	bool attack = dist < (attackDistance * attackDistance);
	bool nothing = dist > (trackDistance * trackDistance);
	if (attack) {
		fsm->SetState("Attack");
	}
	if (nothing) {
		fsm->SetState("Idle");
	}

	float normal = sqrtf(dist);
	float normalX = disX / normal;
	float normalY = disY / normal;

	if (movement != nullptr)
	{
		movement->SetDirection({ normalX, normalY });
	}
}

void EnemyTracking::Exit()
{
	movement->SetSpeed(0.f);
}

#include "EnemyIdle.h"
#include "framework.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"

void EnemyIdle::Enter()
{
	fsm->gameObject->spriteAnim->SetAnimation(0, false);
}

void EnemyIdle::Update(float deltaTime)
{
	float disX = target->transform->m_RelativeLocation.x - fsm->gameObject->transform->m_RelativeLocation.x;
	float disY = target->transform->m_RelativeLocation.y - fsm->gameObject->transform->m_RelativeLocation.y;

	float dist = disX * disX + disY * disY;
	bool inTarget = dist < (distance * distance);

	if (inTarget) {
		fsm->SetState("Tracking");
	}
}

void EnemyIdle::Exit()
{
	
}

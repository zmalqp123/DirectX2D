#include "EnemyAttack.h"
#include "framework.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"
void EnemyAttack::Enter()
{
	fsm->gameObject->spriteAnim->SetAnimation(2, false);
}

void EnemyAttack::Update(float deltaTime)
{
	float disX = target->transform->m_RelativeLocation.x - fsm->gameObject->transform->m_RelativeLocation.x;
	float disY = target->transform->m_RelativeLocation.y - fsm->gameObject->transform->m_RelativeLocation.y;

	float dist = disX * disX + disY * disY;
	bool nothing = dist > (attackDistance * attackDistance);
	if (nothing && fsm->gameObject->spriteAnim->isLastFrame()) {
		fsm->SetState("Tracking");
	}
}

void EnemyAttack::Exit()
{
}

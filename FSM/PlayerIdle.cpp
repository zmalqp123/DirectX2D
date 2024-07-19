#include "PlayerIdle.h"
#include "framework.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimation.h"
void PlayerIdle::Enter()
{
	fsm->gameObject->spriteAnim->SetAnimation(0, false);
}

void PlayerIdle::Update(float deltaTime)
{
	if (GetKeyState(0x44) < 0 || GetKeyState(0x41) < 0 || GetKeyState(0x57) < 0 || GetKeyState(0x53) < 0) {
		fsm->SetState("Tracking");
	}
}

void PlayerIdle::Exit()
{
}

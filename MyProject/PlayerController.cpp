#include "PlayerController.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Camera.h"

void PlayerController::Update(float delta)
{
	Vector2 dir = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition()) - gameObject->transform->m_RelativeLocation;

	Vector2 lerpVec = dir * 0.3f;
	cam->gameObject->transform->m_RelativeLocation = gameObject->transform->m_RelativeLocation + lerpVec;


}

void PlayerController::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void PlayerController::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	pOtherComponent->gameObject->SetActive(false);
}

void PlayerController::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

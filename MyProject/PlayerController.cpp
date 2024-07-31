#include "PlayerController.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/PublicData.h"
#include "../D2DEngine/TextRenderer.h"
int count = 0;
float timer = 0.f;
void PlayerController::Update(float delta)
{
	Vector2 dir = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition()) - gameObject->transform->m_RelativeLocation;

	Vector2 lerpVec = dir * 0.3f;


	cam->gameObject->transform->m_RelativeLocation = gameObject->transform->m_RelativeLocation + lerpVec;
	timer += delta;

	timerObj->GetComponent<TextRenderer>()->text = L"\nTimer: " + std::to_wstring(static_cast<int>(timer)) + L"\n이동: wasd, 회피: spacebar";
}

void PlayerController::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	/*auto pRenderTarget = &D2DRenderer::getRenderTarget();
	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(PublicData::GetInstance().GetScreenSize().x / 2.f, PublicData::GetInstance().GetScreenSize().y / 2.f);
	D2D1_MATRIX_3X2_F Transform =
		gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	pRenderTarget->SetTransform(Transform);

	D2DRenderer::getIncetance().DrawStringTextw(std::to_wstring(count).c_str(), cameraMat, D2D1::ColorF::LimeGreen);*/
}

void PlayerController::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void PlayerController::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	
}

void PlayerController::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void PlayerController::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	if (!isDodgeRoll) {
		count++;
		pOtherComponent->gameObject->SetActive(false);
		cam->gameObject->GetComponent<TextRenderer>()->text = L"Count : " + std::to_wstring(count);
	}
}

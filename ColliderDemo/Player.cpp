#include "Player.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include <iostream>

void Player::Init()
{
}

bool preKey = false;

void Player::Update(float delta)
{
	if (GetKeyState(VK_RIGHT) < 0) {
		gameObject->transform->m_RelativeLocation.x += 1.f;
	}
	else if (GetKeyState(VK_LEFT) < 0) {
		gameObject->transform->m_RelativeLocation.x += -1.f;
	}
	if (GetKeyState(VK_UP) < 0) {
		gameObject->transform->m_RelativeLocation.y += 1.f;
	}
	else if (GetKeyState(VK_DOWN) < 0) {
		gameObject->transform->m_RelativeLocation.y += -1.f;
	}


	if (GetKeyState(VK_SPACE) < 0 && !preKey) {
		//isKeydown = true;
		int size = colls.size();

		if (size > 0) {
			for (int i = 0; i < size; i++) {
				colls[i]->isActive = false;
			}

			count += size;
			colls.clear();
		}
	}
	preKey = false;
	preKey = GetKeyState(VK_SPACE) < 0 ? true : false;
}

void Player::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, 1.0f) *
		D2D1::Matrix3x2F::Translation(0.f, 0.f);

	D2DRenderer::getIncetance().DrawStringTextw(std::to_wstring(count).c_str(), m_ScreenTransform);
}

void Player::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	if (pOtherComponent->gameObject->isActive == true)
		colls.push_back(pOtherComponent->gameObject);
	count++;
}

void Player::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	if (pOtherComponent->gameObject->isActive == true)
		colls.push_back(pOtherComponent->gameObject);
}

void Player::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	colls.erase(remove(colls.begin(), colls.end(), pOtherComponent->gameObject), colls.end());
}

#include "Generator.h"
#include "DropIt.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "cmath"
#include <random>
void Generator::Init()
{
}

void Generator::Update(float delta)
{
	timer += delta;
	if (timer >= maxTimer) {
		timer -= maxTimer;
		if (pools.size() > 0) {
			DropIt* a = pools.top();
			pools.pop();
			int r = rand() % 360;
			a->gameObject->transform->m_RelativeLocation = { 600.f * std::cosf((r - 180) / 180.f * 3.14159f), 600.f * std::sinf((r - 180) / 180.f * 3.14159f) };

			a->SetTarget(target);
			a->gameObject->isActive = true;
		}
		else {
			return;
		}
	}
}

void Generator::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, 1.0f) *
		D2D1::Matrix3x2F::Translation(200.f, 0.f);

	D2DRenderer::getIncetance().DrawStringTextw(L"spacebar를 눌러 날아오는 아이템을 먹습니다.", m_ScreenTransform);
}

#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "D2DRenderer.h"
bool BoxCollider::isCollide(Collider* collider)
{
    if (collider->GetColliderType() == ColliderType::Box) {
		D2D1_MATRIX_3X2_F c = gameObject->transform->m_WorldTransform;

		AABB owner;
		owner.m_Center = {
			c.m[2][0],
			c.m[2][1]
		};
		owner.m_Extent = {
			abs(c.m[0][0] * m_Collider.m_Extent.x + c.m[1][0] * m_Collider.m_Extent.y),
			abs(c.m[0][1] * m_Collider.m_Extent.x + c.m[1][1] * m_Collider.m_Extent.y)
		};

        BoxCollider* pOtherCollider = static_cast<BoxCollider*>(collider);
		D2D1_MATRIX_3X2_F c1 = pOtherCollider->gameObject->transform->m_WorldTransform;
		AABB other;
		other.m_Center = {
			c1.m[2][0],
			c1.m[2][1]
		};
		other.m_Extent = {
			abs(c1.m[0][0] * pOtherCollider->m_Collider.m_Extent.x + c1.m[1][0] * pOtherCollider->m_Collider.m_Extent.y),
			abs(c1.m[0][1] * pOtherCollider->m_Collider.m_Extent.x + c1.m[1][1] * pOtherCollider->m_Collider.m_Extent.y)
		};

        if (!owner.CheckIntersect(other))
            return false;
        return true;
		/*if (!m_Collider.CheckIntersect(pOtherCollider->m_Collider))
            return false;
        return true;*/
    }
    return false;
}

void BoxCollider::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	auto pRenderTarget = &D2DRenderer::getRenderTarget();

	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(640.f, 360.f);
	D2D1_MATRIX_3X2_F Transform =
		gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	pRenderTarget->SetTransform(Transform);
	//pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	D2DRenderer::getIncetance().DrawHollowRectangle(m_Collider.GetMinX(),
		m_Collider.GetMinY(),
		m_Collider.GetMaxX(),
		m_Collider.GetMaxY(),
		2.f,
		D2D1::ColorF::LimeGreen		
		);
}

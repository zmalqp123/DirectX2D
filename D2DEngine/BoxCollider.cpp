#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "D2DRenderer.h"
bool BoxCollider::isCollide(Collider* collider, Vector2& resolution)
{
    if (collider->GetColliderType() == ColliderType::Box) {
		D2D1_MATRIX_3X2_F c = gameObject->transform->m_WorldTransform;

		AABB owner;
		owner.m_Center = {
			c.m[2][0] + offset.x,
			c.m[2][1] + offset.y
		};
		owner.m_Extent = {
			abs(c.m[0][0] * m_Collider.m_Extent.x + c.m[1][0] * m_Collider.m_Extent.y),
			abs(c.m[0][1] * m_Collider.m_Extent.x + c.m[1][1] * m_Collider.m_Extent.y)
		};

        BoxCollider* pOtherCollider = static_cast<BoxCollider*>(collider);
		D2D1_MATRIX_3X2_F c1 = pOtherCollider->gameObject->transform->m_WorldTransform;
		AABB other;
		other.m_Center = {
			c1.m[2][0] + pOtherCollider->offset.x,
			c1.m[2][1] + pOtherCollider->offset.y
		};
		other.m_Extent = {
			abs(c1.m[0][0] * pOtherCollider->m_Collider.m_Extent.x + c1.m[1][0] * pOtherCollider->m_Collider.m_Extent.y),
			abs(c1.m[0][1] * pOtherCollider->m_Collider.m_Extent.x + c1.m[1][1] * pOtherCollider->m_Collider.m_Extent.y)
		};

        if (!owner.CheckIntersect(other, resolution))
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
	if (gameObject->isActive == false) return;
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
	D2DRenderer::getIncetance().DrawHollowRectangle(
		m_Collider.GetMinX(),
		m_Collider.GetMinY(),
		m_Collider.GetMaxX(),
		m_Collider.GetMaxY(),
		2.f,
		D2D1::ColorF::LimeGreen		
	);
}



void BoxCollider::SetOffset(const Vector2& _offset)
{
	offset = _offset;
}

void BoxCollider::SetCenter(const Vector2& _center)
{
	m_Collider.m_Center = _center;
}

void BoxCollider::SetExtent(const Vector2& _extent)
{
	m_Collider.m_Extent = _extent;
}


//collider에 render붙이는거 테스트 중.
AABB BoxCollider::GetBound()
{
	AABB ab;
	ab.SetCenter(gameObject->transform->m_WorldTransform.dx, gameObject->transform->m_WorldTransform.dy);
	ab.SetExtent(m_Collider.m_Extent.x, m_Collider.m_Extent.y);
	return ab;
}

void BoxCollider::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false) return;

	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(640.f, 360.f);
	D2D1_MATRIX_3X2_F Transform =
		gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	pRenderTarget->SetTransform(Transform);
	//pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	D2DRenderer::getIncetance().DrawHollowRectangle(
		m_Collider.GetMinX(),
		m_Collider.GetMinY(),
		m_Collider.GetMaxX(),
		m_Collider.GetMaxY(),
		2.f,
		D2D1::ColorF::LimeGreen
	);
}

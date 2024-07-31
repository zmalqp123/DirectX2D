#include "pch.h"
#include "Texture.h"
#include "SpriteAnimation.h"
#include "SpriteAnimationAsset.h"

#include "D2DRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"

#include "AABB.h"

SpriteAnimation::SpriteAnimation()
{

}

SpriteAnimation::~SpriteAnimation()
{
	// ���ҽ��Ŵ����� ���Ͽ� �����̸����� �����Ѵ�.
	if (m_pAnimationAsset)
	{
		ResourceManager::GetInstance().ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationAsset = nullptr;
	}
}

void SpriteAnimation::LoadAnimationAsset(const std::wstring strFilePath)
{
	// ���ҽ� �Ŵ����� ���� AnimationAsset�� �ε��Ѵ�.
	m_strAnimationAssetFilePath = strFilePath;

	ResourceManager::GetInstance().CreateAnimationAsset(m_strAnimationAssetFilePath, &m_pAnimationAsset);
}

void SpriteAnimation::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);
	assert(m_pAnimationAsset != nullptr);  // asset�� ������ debug��忡�� ����
	if (m_pAnimationInfo == nullptr)
		return;

	size_t MaxFrameCount = m_pAnimationInfo->Frames.size();
	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	m_FrameTime += fTimeElapsed;
	if (m_FrameTime >= Frame.Duration) {
		m_FrameTime -= Frame.Duration;
		m_FrameIndexCurr = (m_FrameIndexCurr + 1) % m_pAnimationInfo->Frames.size();
	}

	///////////////     
	// m_FrameTime�� fTimeElapsed�� ��������  Frame.Duration���� ũ�� 
	// m_FrameIndexCurr�� ������Ű�� m_FrameTime�� 0���� �ʱ�ȭ�Ѵ�.
	// �ϴ� ������ �����ϰ� ó���Ѵ�.
	////////////////


	m_SrcRect = Frame.Source;
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_bMirror) //x �� �������� �¿� ���� , Translation �� ����� �̹����� ���� ����
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
}

void SpriteAnimation::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
		return;
	if (m_pAnimationInfo == nullptr)
		return;
	D2D1_MATRIX_3X2_F m_ScreenTransform = 
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(640.f, 360.f);
	D2D1_MATRIX_3X2_F Transform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_ImageTransform
		* gameObject->transform->m_WorldTransform
		* cameraMat 
		* m_ScreenTransform;
	;// * D2DRenderer::m_CameraTransform;
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, m_SrcRect);
}

void SpriteAnimation::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
		return;
	if (m_pAnimationInfo == nullptr)
		return;
	auto pRenderTarget = &D2DRenderer::getRenderTarget();

	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(640.f, 360.f);
	D2D1_MATRIX_3X2_F Transform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_ImageTransform
		* gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	//  * D2DRenderer::m_CameraTransform;
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, m_SrcRect);
}

void SpriteAnimation::SetAnimation(int index, bool mirror, bool continueCurrentFrame)
{
	assert(m_pAnimationAsset != nullptr);

	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimationInfo(index);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_bMirror = mirror;
	if (!continueCurrentFrame) {
		m_FrameIndexCurr = 0;
		m_FrameIndexPrev = 0;
		m_FrameTime = 0.0f;
	}
	else {
		m_FrameIndexCurr = m_FrameIndexCurr % m_pAnimationInfo->Frames.size();
		m_FrameIndexPrev = 0;
	}
}

AABB SpriteAnimation::GetBound()
{
	AABB ab;
	ab.SetCenter(gameObject->transform->m_WorldTransform.dx , gameObject->transform->m_WorldTransform.dy);
	ab.SetExtent(float((m_DstRect.right - m_DstRect.left) / 2), float((m_DstRect.bottom - m_DstRect.top) / 2));
	return ab;
}

int SpriteAnimation::GetMaxIndex()
{
	return m_pAnimationInfo->Frames.size();
}

bool SpriteAnimation::IsLastFrame()
{
	return m_pAnimationInfo->Frames.size() - 1 == m_FrameIndexCurr;
}

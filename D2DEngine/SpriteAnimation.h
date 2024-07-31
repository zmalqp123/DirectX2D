#pragma once
#include "Renderer.h"


class SpriteAnimationAsset;
struct ANIMATION_INFO;
class Transform;
class Texture;
class AABB;
class SpriteAnimation : public Renderer
{
public:
	SpriteAnimation();
	virtual ~SpriteAnimation();

	// �����ϴ� �ִϸ��̼� ����	
	SpriteAnimationAsset* m_pAnimationAsset = nullptr;  // �����ϴ� �ִϸ��̼� ����

	// �ν��Ͻ����� �ٸ� �ִϸ��̼� ����
	ANIMATION_INFO* m_pAnimationInfo = nullptr;	// ���� �ִϸ��̼� ������ ����
	std::wstring m_strAnimationAssetFilePath;    // �ִϸ��̼� ���� ���� �̸�
	float m_FrameTime = 0.0f;	// ������ ����ð�
	int m_FrameIndexCurr = -1;	// ���� ������ �ε���
	int m_FrameIndexPrev = -1;	// ���� ������ �ε���
	int m_AnimationIndex = -1;	// ���� �ִϸ��̼� �ε���
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget�� Destination ����		

	bool m_bMirror;				// �¿� ���� ����
	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 
	Texture* m_pTexture;

	void LoadAnimationAsset(const std::wstring strFilePath);
	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);
	void SetAnimation(int index, bool mirror, bool continueCurrentFrame = false);

	AABB GetBound();

	int GetMaxIndex();

	bool IsLastFrame();
};


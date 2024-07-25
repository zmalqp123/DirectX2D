#pragma once
#include "Renderer.h"

class Transform;
class Texture;
class AABB;
class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();

	Texture* m_pTexture = nullptr;

	std::wstring m_strTextureFilePath;
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget�� Destination ����

	bool m_flipX;
	bool m_flipY;

	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	void LoadTexture(const std::wstring strFilePath);
	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);

	AABB GetBound();
};


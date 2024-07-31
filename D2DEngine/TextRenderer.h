#pragma once
#include "Renderer.h"

class Transform;
class Texture;
class AABB;
class TextRenderer : public Renderer
{
public:
	TextRenderer();
	virtual ~TextRenderer();

	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget�� Destination ����

	bool m_flipX;
	bool m_flipY;

	std::wstring text = L"";

	D2D1::ColorF color = D2D1::ColorF::LimeGreen;

	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);

	AABB GetBound();
};


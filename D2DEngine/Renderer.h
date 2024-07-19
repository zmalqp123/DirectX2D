#pragma once
#include "Component.h"
class Renderer : public Component
{
public:
	Renderer() {}
	virtual ~Renderer() {}

	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat) = 0;
};


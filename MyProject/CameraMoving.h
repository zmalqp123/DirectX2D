#pragma once
#include "../D2DEngine/Component.h"

class Transform;
class CameraMoving : public Component
{
public:
	Transform* cameraTr;
	Transform* playerTr;

	void virtual Init() {};
	void virtual Update(float delta) {};
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat) {};
};


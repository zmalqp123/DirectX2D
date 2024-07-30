#pragma once
#include "../D2DEngine/Component.h"
#include <stack>
class Transform;
class Bullet;
class Generator : public Component
{
	float timer = 0.f;
	float maxTimer = 0.5f;
public:
	Transform* target = nullptr;
	std::stack<Bullet*> pools;
	void virtual Init();
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat);
};


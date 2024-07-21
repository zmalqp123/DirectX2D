#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
#include <vector>
class Player : public Component, public IColliderNotify
{
private:
	std::vector<GameObject*> colls;
	int count = 0;
public:
	void virtual Init();
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat);

	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};


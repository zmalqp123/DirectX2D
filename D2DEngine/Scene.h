#pragma once
#include "Object.h"
#include "GameObject.h"
#include "AABB.h"
#include <vector>
//class GameObject;
class D2DRenderer;
class Scene : public Object
{
public:
	Scene();
	virtual ~Scene();

	std::vector<GameObject*> m_GameObjects;

	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;

	GameObject* cam = nullptr;
	D2D1_MATRIX_3X2_F cameraMat;

	void Start();
	void Update(float deltaTime);
	void Render(D2DRenderer* _render);
	void Clear();
	void SetCullingBound(AABB* pBound);
	
	template<typename T>
	T* CreateGameObject() {
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject�� ��ӹ��� Ŭ������ ������ �� �ִ�.
		T* newObject = new T();
		//newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}
};


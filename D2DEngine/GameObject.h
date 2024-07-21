#pragma once
#include "Object.h"
#include <iostream>
#include <string>
#include <vector>
#include "Collider.h"
class Component;
class Transform;
class SpriteAnimation;

// 게임 오브젝트가 게임오브젝트를 자식으로 가지는 1번
// 모든 게임 오브젝트를 씬에 종속시키고 게임오브젝트가 
// 비활성화 시 상위 오브젝트의 active를 추적하여 실행여부를 결정하는 2번

class GameObject : public Object
{
public:
	bool isActive = true;
	Transform* transform = nullptr;
	SpriteAnimation* spriteAnim = nullptr;

	std::vector<Component*> components;

	GameObject();
	virtual ~GameObject();
	
	virtual void Init();
	virtual void Update(float delta);
	virtual void Render(D2D1_MATRIX_3X2_F cameraMat);

	bool AddComponent(Component* component);
	
	template <typename T>
	T* CreateComponent() {
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);
		T* component = new T();
		components.push_back(component);
		component->SetOwner(this);
		return component;
	}

	template <typename T>
	T* GetComponent() {
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);

		T* pComponent = new T();
		AddComponent(pComponent);

		return pComponent;
	}

	void RemoveComponent(Component* Component);

	void SetActive(bool active);
};


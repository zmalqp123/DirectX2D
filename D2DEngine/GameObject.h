#pragma once
#include "Object.h"
#include <iostream>
#include <string>
#include <vector>
#include "Collider.h"
class Component;
class Transform;
class SpriteAnimation;

// ���� ������Ʈ�� ���ӿ�����Ʈ�� �ڽ����� ������ 1��
// ��� ���� ������Ʈ�� ���� ���ӽ�Ű�� ���ӿ�����Ʈ�� 
// ��Ȱ��ȭ �� ���� ������Ʈ�� active�� �����Ͽ� ���࿩�θ� �����ϴ� 2��

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


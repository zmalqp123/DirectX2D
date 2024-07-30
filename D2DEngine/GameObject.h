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
		//assert(bIsBase == true);
		T* component = new T();
		components.push_back(component);
		component->SetOwner(this);
		return component;
	}

	template <typename T>
	T* GetComponent() {
		bool bIsBase = std::is_base_of<Component, T>::value;
		//assert(bIsBase == true);

		for (auto iter = components.begin(); iter != components.end(); iter++)
		{
			T* result= dynamic_cast<T*>(*iter);
			if (result) return result;
		}

		//// ��Ӱ����� ������Ʈ�� ã�� �� ����.
		//for (auto c : components) {
		//	auto cP = dynamic_cast<T*>(c);
		//	if (cP != nullptr) {
		//		if (typeid(cP) == typeid(T*)) {
		//			return dynamic_cast<T*>(c);
		//		}
		//	}
		//	if (typeid(*c) == typeid(T))
		//		return dynamic_cast<T*>(c);
		//}
		//return nullptr;
	}

	void RemoveComponent(Component* Component);

	void SetActive(bool active);
};


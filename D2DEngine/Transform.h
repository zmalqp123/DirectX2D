#pragma once
#include "Component.h"
#include "Vector.h"
class Transform : public Component
{
public:
	Transform() {};
	virtual ~Transform() {};

public:
	Transform*			m_pParentScene = nullptr;	// �θ� Scene ������Ʈ	
	Vector2		m_RelativeScale = { 1,1 };	// ��� ũ��
	float				m_RelativeRotation = 0;		// ��� ȸ��
	Vector2 		m_RelativeLocation = { 0,0 }; // ��� ��ġ
	D2D1_MATRIX_3X2_F	m_RelativeTransform;		// ��� ���� ��ȯ
	D2D1_MATRIX_3X2_F	m_WorldTransform;			// �θ���� �ݿ��� ���� ��ȯ

	//Vector2		m_CenterTransform;

	// RelativeTransform�� m_WorldTransform�� ����Ѵ�.
	void UpdateTrasnform();
	void SetParent(Transform* pParentScene) { m_pParentScene = pParentScene; }
};


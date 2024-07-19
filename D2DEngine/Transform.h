#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform() {};
	virtual ~Transform() {};

public:
	Transform*			m_pParentScene = nullptr;	// �θ� Scene ������Ʈ	
	D2D1_VECTOR_2F		m_RelativeScale = { 1,1 };	// ��� ũ��
	float				m_RelativeRotation = 0;		// ��� ȸ��
	D2D1_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // ��� ��ġ
	D2D1_MATRIX_3X2_F	m_RelativeTransform;		// ��� ���� ��ȯ
	D2D1_MATRIX_3X2_F	m_WorldTransform;			// �θ���� �ݿ��� ���� ��ȯ

	D2D1_VECTOR_2F		m_CenterTransform;

	// RelativeTransform�� m_WorldTransform�� ����Ѵ�.
	void UpdateTrasnform();
	void SetParent(Transform* pParentScene) { m_pParentScene = pParentScene; }
};


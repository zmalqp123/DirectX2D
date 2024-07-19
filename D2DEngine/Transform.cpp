#include "pch.h"
#include "Transform.h"


void Transform::UpdateTrasnform()
{
	m_RelativeTransform = 
		//D2D1::Matrix3x2F::Translation(m_CenterTransform.x, m_CenterTransform.y) *     // ��� �����ܰ迡�� ���� ����ؾ� ����. ��������Ʈ �ǹ�
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	// ���� ���� ������� �������� ��Ʈ������ ������ �ְ� (pivot, scale, rotation) �� ���� transform�� matrix�� ���Ͽ� ǥ���ؾ� �ҰŰ���.

	if (m_pParentScene != nullptr)
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	else
		m_WorldTransform = m_RelativeTransform;
}
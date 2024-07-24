#pragma once
#include "Vector.h"
/*
	AABB (Axis-Aligned Bounding Box) �� ���ĵ� ��� ����

	  +y
	  ^
	  |         +----------------------max
	  |         |                      |
	  |         |		 center        |
	  |	        |          +---------- |
	  |         |          |  extend.x |
	  |         |  extend.y|           |
	  |         min--------------------+
	--+------------------------------------> +x
   0,0
*/
class AABB
{
public:
	AABB() : m_Center{ 0.f, 0.f }, m_Extent{ 0.f, 0.f } { }
public:
	Vector2 m_Center; // �߾�
	Vector2 m_Extent; // x,y�� Ȯ�尪	
	// minX = m_Center.x - m_Extent.x
	// maxX = m_Center.x + m_Extent.x
	// minY = m_Center.y - m_Extent.y
	// maxY = m_Center.y + m_Extent.y

	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;
	AABB(AABB&&) = default;
	AABB& operator=(AABB&&) = default;
	~AABB() = default;

	void SetCenter(float x, float y) { m_Center = { x, y }; }
	void SetExtent(float x, float y) { m_Extent = { x, y }; }
	float GetMinX() { return m_Center.x - m_Extent.x; }
	float GetMaxX() { return m_Center.x + m_Extent.x; }
	float GetMinY() { return m_Center.y - m_Extent.y; }
	float GetMaxY() { return m_Center.y + m_Extent.y; }

	bool CheckIntersect(const AABB& other) const
	{
		// self min,max
		float BoxA_xmin = m_Center.x - m_Extent.x;
		float BoxA_xmax = m_Center.x + m_Extent.x;
		float BoxA_ymin = m_Center.y - m_Extent.y;
		float BoxA_ymax = m_Center.y + m_Extent.y;

		// other min,max
		float BoxB_xmin = other.m_Center.x - other.m_Extent.x;
		float BoxB_xmax = other.m_Center.x + other.m_Extent.x;
		float BoxB_ymin = other.m_Center.y - other.m_Extent.y;
		float BoxB_ymax = other.m_Center.y + other.m_Extent.y;

		// Check for no overlap conditions
		if (BoxA_xmax < BoxB_xmin ||  // �����ʿ� ������ ��ĥ���� ����
			BoxA_xmin > BoxB_xmax ||  // ���ʿ� ������ ��ĥ���� ����
			BoxA_ymax < BoxB_ymin ||  // �Ʒ��� ������ ��ĥ���� ����
			BoxA_ymin > BoxB_ymax)	  // ���� ������ ��ĥ���� ����
		{
			return false;
		}

		return true;

	}

	bool CheckIntersect(const AABB& other, Vector2& resolution) {
		// self min,max
		float BoxA_xmin = m_Center.x - m_Extent.x;
		float BoxA_xmax = m_Center.x + m_Extent.x;
		float BoxA_ymin = m_Center.y - m_Extent.y;
		float BoxA_ymax = m_Center.y + m_Extent.y;

		// other min,max
		float BoxB_xmin = other.m_Center.x - other.m_Extent.x;
		float BoxB_xmax = other.m_Center.x + other.m_Extent.x;
		float BoxB_ymin = other.m_Center.y - other.m_Extent.y;
		float BoxB_ymax = other.m_Center.y + other.m_Extent.y;

		float overlapX1 = BoxB_xmax - BoxA_xmin;
		float overlapX2 = BoxA_xmax - BoxB_xmin;
		float overlapY1 = BoxB_ymax - BoxA_ymin;
		float overlapY2 = BoxA_ymax - BoxB_ymin;

		float minOverlapX = (overlapX1 < overlapX2) ? overlapX1 : -overlapX2;
        float minOverlapY = (overlapY1 < overlapY2) ? overlapY1 : -overlapY2;

		resolution = { 0.f, 0.f };

        if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
            resolution.x = minOverlapX;
        } else {
            resolution.y = minOverlapY;
        }

		// Check for no overlap conditions
		if (BoxA_xmax < BoxB_xmin ||  // �����ʿ� ������ ��ĥ���� ����
			BoxA_xmin > BoxB_xmax ||  // ���ʿ� ������ ��ĥ���� ����
			BoxA_ymax < BoxB_ymin ||  // �Ʒ��� ������ ��ĥ���� ����
			BoxA_ymin > BoxB_ymax)	  // ���� ������ ��ĥ���� ����
		{
			return false;
		}

		return true;
	}
};


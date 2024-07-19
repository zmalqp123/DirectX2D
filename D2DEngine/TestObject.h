#pragma once
#include "Transform.h"
class TestObject
{
private:
	//std::wstring m_strFileName;
	WCHAR m_strFileName[255];
public:
	ID2D1Bitmap* m_pBitmap = nullptr;
	Transform* transform = nullptr;
	D2D1_VECTOR_2F DestPos{ 0,0 }, SrcPos{ 0,0 }; // ȭ�� ��ġ, ��Ʈ�� ��ġ
	D2D1_SIZE_F size{ 0,0 }; //	�׸� ũ��
	D2D1_RECT_F DestRect{ 0,0,0,0 }, SrcRect{ 0,0,0,0 }; // ȭ�� ����, ��Ʈ�� ����

	TestObject(const WCHAR* strFileName)
	{
		wcscpy_s(m_strFileName, 255, strFileName);
		Init(); 
	}
	virtual ~TestObject() {};

	void Init();
	void Update();
	void Render();
	void UnInit();

	bool Load(const WCHAR* strFileName);
};


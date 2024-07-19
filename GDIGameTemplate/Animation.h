#pragma once

// ������ �ϳ��� ������ ����
struct Frame
{
	RECT Source = {0,};			// �κ������ �̹��� ����
	SIZE Size = {0,};			// ��� ũ��
	int CenterX=0,CenterY=0;	// �߽��� �Ǵ� �̵� ��ġ 
};

struct Motion 
{
	Frame Frames[20];		// ������ �����̳�
	int FrameCount=0;			// ��ü ������ ��
	bool IsLoop = false;	// �ݺ� ����
};

struct AnimationResource
{	
	std::wstring m_fileName;	

	Gdiplus::Bitmap* m_bitmap = nullptr;		// Origin Image
	Gdiplus::Bitmap* m_bitmapFlip = nullptr;	// Flip Image
	Motion m_motions[10];	// �ִ� 10���� ������ ���� �� ����
	int m_motionCount = 0;	// ���� ������ ����

	~AnimationResource();	// GDI+�� �ı��Ǳ����� ��Ʈ�� �޸� �����ؾ��Ѵ�.

	void LoadAnimImage(const WCHAR* fileName);
	void LoadAnimMotion(const WCHAR* fileName,bool IsLoop=true);
};


#pragma once
#include "Object.h"


// �ؽ��Ĵ� �̹����� ������ ������ �ִٰ�
// sprite�� �ؽ�ó�� ������ ��
// center, scale, rotate ���� ��������� sprite�� ������ �ִٰ�
// �� ���� ������Ʈ�� �����ؼ� ����ϴ� ������� ����

// texture, sprite�� referenceCounter�� �����޴´�.
// ex) texture�� ������� sprite�� �������� �ɰ��� �����ߴٰ�
// �ִϸ��̼ǿ��� sprite�� �迭�� ��� ����ϴ� �������.

// Ÿ���� single, multiple�� �����ϰ�
class Texture;
class Sprite : public Object
{
	// �̸�
	std::wstring m_Name;

	// ��Ʈ��
	Texture* m_pTexture = nullptr;

	// �̹����� pivot��ǥ
	D2D1_VECTOR_2F		m_PivotTransform;

	// �̹����� border��ǥ
	D2D1_VECTOR_4F		m_BorderTransform;

	// �̹����� ũ��		ex) ������ǥ (0, 0), ����ǥ (width - 1, height - 1)
	D2D1_SIZE_F			m_SpriteSize;

	// �̹������� �׸� ����
	D2D1_RECT_F			m_Source;

	Sprite(Texture* _pTexture);
	Sprite(Texture* _pTexture, D2D1_VECTOR_2F _pivot);
	Sprite(Texture* _pTexture, D2D1_VECTOR_2F _pivot, D2D1_RECT_F _Source);
	virtual ~Sprite();
};

class Texture : public Object
{
public:
	// 0 = Default, 1 = Sprite 
	Texture(std::wstring _Filepath, ID2D1Bitmap* _pD2DBitmap);
	virtual ~Texture();

	std::wstring m_Filepath;
	ID2D1Bitmap* m_pD2DBitmap = nullptr;

	Sprite* sprite = nullptr;
	std::vector<Sprite*> multipleSprite;
};


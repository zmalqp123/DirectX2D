#pragma once
#include <windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <d2d1_1helper.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <comdef.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib,"windowscodecs.lib")
#include <dxgi1_4.h>
//#include <string>

class D2DRenderer
{
	D2DRenderer() {}
	D2DRenderer(const D2DRenderer& ref) {}
	D2DRenderer& operator=(const D2DRenderer& ref) {}
	~D2DRenderer() {}

	//  D2D ��ü �������̽� ������ ����
	ID2D1Factory* _D2DFactory = nullptr;

	// ī�޶�� �ϳ� ���� ������ �˰��ֱ� matrix�� ����ؼ� transform�� ��ȯ�ϸ� ����Ÿ���� ���� ��µǴ� �̹��� ���� ��ġ�� ���� ����.
	ID2D1HwndRenderTarget* _RenderTarget = nullptr;

	ID2D1SolidColorBrush* g_brush = nullptr;
	
	// Image
	IWICImagingFactory* g_pWICFactory = nullptr;
	ID2D1Bitmap* g_pD2DBitmap = nullptr;

	// DWrite
	IDWriteFactory* g_pDWriteFactory = nullptr;
	IDWriteTextFormat* g_pDWriteTextFormat = nullptr;

	IDXGIFactory4* m_pDXGIFactory = nullptr;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter = nullptr;		// ����ī�� ������ ���� ������ �������̽�

public:
	static D2DRenderer& getIncetance() {
		static D2DRenderer instance;
		return instance;
	}

	static ID2D1HwndRenderTarget& getRenderTarget() {
		return *getIncetance()._RenderTarget;
	}

	bool InitDirect2D(HWND hWnd);
	void UnInitDirect2D();
	void BeginDraw();
	void Clear(D2D1::ColorF color);
	void Render();
	void EndDraw();
public:
	void DrawRectangle(float x1, float y1, float x2, float y2, D2D1::ColorF color);
	void DrawLine(D2D1_POINT_2F p0, D2D1_POINT_2F p1, float width, D2D1::ColorF color, D2D1_MATRIX_3X2_F transform);
	void DrawHollowRectangle(float x1, float y1, float x2, float y2, float width, D2D1::ColorF color);
	
	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	void DrawBitmap(ID2D1Bitmap* pBitmap, D2D1_MATRIX_3X2_F transform);

	void DrawStringText(const WCHAR* _text);
	void DrawStringTextw(const WCHAR* _text, D2D1_MATRIX_3X2_F transform, D2D1::ColorF color = D2D1::ColorF::Black);

	size_t GetUsedVRAM();

};


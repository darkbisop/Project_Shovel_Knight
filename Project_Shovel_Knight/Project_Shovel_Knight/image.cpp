#include "stdafx.h"
#include "image.h"
#include "animation.h"

#pragma comment (lib, "msimg32.lib")

image::image()
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, 
		WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//HRESULT image::init(const char * szFileName, int width, int height)
//{
//	if (szFileName == NULL) return E_FAIL;
//
//	HDC hdc = GetDC(g_hWnd);
//
//	m_pImageInfo = new IMAGE_INFO;
//	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
//	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
//	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
//	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
//		g_hInstance, 
//		szFileName,
//		IMAGE_BITMAP,
//		width, height,
//		LR_LOADFROMFILE);
//	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
//	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);
//
//	m_pImageInfo->nWidth = width;
//	m_pImageInfo->nHeight = height;
//
//	ReleaseDC(g_hWnd, hdc);
//
//	if (m_pImageInfo->hBitmap == NULL)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}

HRESULT image::init(const char * szFileName, int width, int height, bool trans /*= false*/, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// �ǰ� ����
	m_blendFuncHit.AlphaFormat = 0;
	m_blendFuncHit.BlendFlags = 0;
	m_blendFuncHit.BlendOp = AC_SRC_OVER;

	m_pBlendImageHit = new IMAGE_INFO;
	m_pBlendImageHit->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImageHit->hBitmap = CreateCompatibleBitmap(hdc, m_pImageInfo->nWidth, m_pImageInfo->nHeight);
	m_pBlendImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pBlendImageHit->hMemDC, m_pBlendImageHit->hBitmap);
	m_pBlendImageHit->nWidth = m_pImageInfo->nWidth;
	m_pBlendImageHit->nHeight = m_pImageInfo->nHeight;

	// �귯�� ���� �̹��� �غ�
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_pBlendImageHit->hMemDC, brush);
	FillRect(m_pBlendImageHit->hMemDC, &RectMake(0, 0, m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight), brush);
	SelectObject(m_pBlendImageHit->hMemDC, oldBrush);
	DeleteObject(brush);

	//for (int y = 0; y < m_pBlendImageHit->nHeight; y++)
	//{
	//	for (int x = 0; x < m_pBlendImageHit->nWidth; x++)
	//	{
	//		COLORREF color = GetPixel(m_pImageInfo->hMemDC, x, y);
	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);
	//		if (!(r == 255 && g == 0 && b == 255))
	//		{
	//			SetPixel(m_pBlendImageHit->hMemDC, x, y, RGB(255, 0, 0));
	//		}
	//		else
	//		{
	//			SetPixel(m_pBlendImageHit->hMemDC, x, y, RGB(255, 0, 255));
	//		}
	//	}
	//}

	m_pTempImageHit = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pTempImageHit->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pTempImageHit->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pTempImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pTempImageHit->hMemDC, m_pTempImageHit->hBitmap);

	m_pTempImageHit->nWidth = width;
	m_pTempImageHit->nHeight = height;

	// ���� �÷� ����
	m_isTransparent = trans;
	m_transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char * szFileName, float x, float y,
	int width, int height, int frameX, int frameY,
	bool trans, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->fX = x;
	m_pImageInfo->fY = y;
	m_pImageInfo->nCurrFrameX = 0;
	m_pImageInfo->nCurrFrameY = 0;
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// �ǰ� ����
	m_blendFuncHit.AlphaFormat = 0;
	m_blendFuncHit.BlendFlags = 0;
	m_blendFuncHit.BlendOp = AC_SRC_OVER;

	m_pBlendImageHit = new IMAGE_INFO;
	m_pBlendImageHit->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImageHit->hBitmap = CreateCompatibleBitmap(hdc, m_pImageInfo->nFrameWidth, m_pImageInfo->nFrameHeight);
	m_pBlendImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pBlendImageHit->hMemDC, m_pBlendImageHit->hBitmap);
	m_pBlendImageHit->nWidth = m_pImageInfo->nFrameWidth;
	m_pBlendImageHit->nHeight = m_pImageInfo->nFrameHeight;

	//for (int y = 0; y < m_pBlendImageHit->nHeight; y++)
	//{
	//	for (int x = 0; x < m_pBlendImageHit->nWidth; x++)
	//	{
	//		COLORREF color = GetPixel(m_pImageInfo->hMemDC, x, y);
	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);
	//		if (!(r == 255 && g == 0 && b == 255))
	//		{
	//			SetPixel(m_pBlendImageHit->hMemDC, x, y, RGB(255, 0, 0));
	//		}
	//		else
	//		{
	//			SetPixel(m_pBlendImageHit->hMemDC, x, y, RGB(255, 0, 255));
	//		}
	//	}
	//}

	m_pTempImageHit = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pTempImageHit->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pTempImageHit->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pTempImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pTempImageHit->hMemDC, m_pTempImageHit->hBitmap);

	m_pTempImageHit->fX = x;
	m_pTempImageHit->fY = y;
	m_pTempImageHit->nCurrFrameX = 0;
	m_pTempImageHit->nCurrFrameY = 0;
	m_pTempImageHit->nWidth = width;
	m_pTempImageHit->nHeight = height;
	m_pTempImageHit->nFrameWidth = width / frameX;
	m_pTempImageHit->nFrameHeight = height / frameY;
	m_pTempImageHit->nMaxFrameX = frameX - 1;
	m_pTempImageHit->nMaxFrameY = frameY - 1;

	// ���� �÷� ����
	m_isTransparent = trans;
	m_transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void image::release()
{
	if (m_pBlendImage)
	{
		SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hOldBitmap);
		DeleteObject(m_pBlendImage->hBitmap);
		DeleteDC(m_pBlendImage->hMemDC);

		delete m_pBlendImage;
	}

	if (m_pImageInfo)
	{
		SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOldBitmap);
		DeleteObject(m_pImageInfo->hBitmap);
		DeleteDC(m_pImageInfo->hMemDC);

		delete m_pImageInfo;
	}
}

void image::render(HDC hdc)
{
	if (m_isTransparent) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ô� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,                  //������ ����� DC
			0,                  //����� ��ǥ ������ x
			0,                  //����� ��ǥ ������ y
			m_pImageInfo->nWidth,         //����� �̹��� ����ũ��
			m_pImageInfo->nHeight,         //����� �̹��� ����ũ��
			
			m_pImageInfo->hMemDC,         //����� ��� DC
			0, 0,                  //���� ��������
			m_pImageInfo->nWidth,         //���� ���� ����ũ��
			m_pImageInfo->nHeight,         //���� ���� ����ũ��
			m_transColor               //�����Ҷ� ������ ����(����Ÿ���� �����)
		);
	}
	else //���� �̹��� �״�� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// ����� ũ��
			
			// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			0, 0,					// ����� ���� ������ǥ
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		// hdc : ����� ������ DC
		// destX : ����� ������ x ��ǥ
		// destY : ����� ������ y ��ǥ
		// cx : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// cy : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// hdcSrc : ������ ������ �����ϴ� DC
		// x1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// y1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// rop : �����ϴ� �ɼ� (SRCCOPY)
		BitBlt(
			hdc, 
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int width, int height)
{
	SetStretchBltMode(hdc, COLORONCOLOR);
	if (m_isTransparent)
	{
		// GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� ����
		GdiTransparentBlt(
			hdc,							// ����� ����� DC
			destX,							// ����� ��ǥ ������ x
			destY,							// ����� ��ǥ ������ y
			width,							// ����� �̹��� ����
			height,						// ����� �̹��� ����
			m_pImageInfo->hMemDC,		// ����� ��� DC
			0,								// ���� ���� x
			0,								// ���� ���� y
			m_pImageInfo->nWidth,			// ���� ���� ����
			m_pImageInfo->nHeight,		// ���� ���� ����
			m_transColor);					// ���� ����
	}
	else
	{
		StretchBlt(hdc, destX, destY, width, height, m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, 
	int sourX, int sourY, int sourWidth, int sourHeight, int scalar)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,					// ����� ������ DC
			destX, destY,			// ����� ��ǥ ������
			sourWidth * scalar, sourHeight * scalar,	// ����� ũ��

			// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			sourX, sourY,			// ����� ���� ������ǥ
			sourWidth, sourHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			sourX, sourY,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		GdiTransparentBlt(
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// ����� ���� ������ǥ
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, BYTE alpha)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;
	m_blendFunc.SourceConstantAlpha = alpha;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		BitBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			hdc,
			destX, destY,
			SRCCOPY);
		GdiTransparentBlt(
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// ����� ���� ������ǥ
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
		AlphaBlend(
			// ������
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}

	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(
			// ������
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani, int scalar)
{
	render(hdc, destX, destY,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight(), scalar);
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	// offset���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = m_pImageInfo->nWidth + (offsetX % m_pImageInfo->nWidth);
	if (offsetY < 0) offsetY = m_pImageInfo->nHeight + (offsetY % m_pImageInfo->nHeight);

	// �׷����� �ҽ��� ����(�̹���)�� ������ ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// �׷����� DC ����
	RECT rcDest;

	// �׷����� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	// ���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		// �ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % m_pImageInfo->nHeight;
		rcSour.bottom = m_pImageInfo->nHeight;
		sourHeight = rcSour.bottom - rcSour.top;

		// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ�� ������ ������ ��)
		if (y + sourHeight > drawAreaH)
		{
			// �Ѿ �׸��� ����ŭ ���� ���� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// �׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// ���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			// �ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % m_pImageInfo->nWidth;
			rcSour.right = m_pImageInfo->nWidth;
			sourWidth = rcSour.right - rcSour.left;

			// �ҽ� ������ �׸��� ȭ���� �Ѿ��
			if (x + sourWidth > drawAreaW)
			{
				// �Ѿ ��ŭ ����Ʈ ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			// �׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// �׷�����
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

void image::hitRender(HDC hdc, int destX, int destY, COLORREF color)
{
	//// �귯�� ���� �̹��� �غ�
	//HBRUSH brush = CreateSolidBrush(color);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(m_pBlendImageHit->hMemDC, brush);

	//BitBlt(
	//	// ������
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,

	//	// ���
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	PATCOPY);

	//SelectObject(m_pBlendImageHit->hMemDC, oldBrush);
	//DeleteObject(brush);

	// �ӽ� �̹��� �غ�
	BitBlt(
		// ������
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,

		// ���
		m_pImageInfo->hMemDC,
		0, 0,
		SRCCOPY);

	// �귯�� + �ӽ�
	BitBlt(
		// ������
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,

		// ���
		m_pBlendImageHit->hMemDC,
		0, 0,
		SRCPAINT);

	if (m_isTransparent)
	{
		// �ӽ� �̹��� ���
		GdiTransparentBlt(
			// ������
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ���
			m_pTempImageHit->hMemDC,
			0, 0,
			m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,
			m_transColor);
	}
	else
	{
		// �ӽ� �̹��� ���
		BitBlt(
			// ������
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ���
			m_pTempImageHit->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void image::hitRender(HDC hdc, int destX, int destY, COLORREF color, int scalar)
{
	//// �귯�� ���� �̹��� �غ�
	//HBRUSH brush = CreateSolidBrush(color);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(m_pBlendImageHit->hMemDC, brush);

	//BitBlt(
	//	// ������
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,

	//	// ���
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	PATCOPY);

	//SelectObject(m_pBlendImageHit->hMemDC, oldBrush);
	//DeleteObject(brush);

	// �ӽ� �̹��� �غ�
	BitBlt(
		// ������
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth * scalar, m_pTempImageHit->nHeight * scalar,

		// ���
		m_pImageInfo->hMemDC,
		0, 0,
		SRCCOPY);

	// �귯�� + �ӽ�
	BitBlt(
		// ������
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth * scalar, m_pTempImageHit->nHeight * scalar,

		// ���
		m_pBlendImageHit->hMemDC,
		0, 0,
		SRCPAINT);

	if (m_isTransparent)
	{
		// �ӽ� �̹��� ���
		GdiTransparentBlt(
			// ������
			hdc,
			destX, destY,
			m_pImageInfo->nWidth * scalar, m_pImageInfo->nHeight * scalar,
			// ���
			m_pTempImageHit->hMemDC,
			0, 0,
			m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,
			m_transColor);
	}
	else
	{
		// �ӽ� �̹��� ���
		BitBlt(
			// ������
			hdc,
			destX, destY,
			m_pImageInfo->nWidth * scalar, m_pImageInfo->nHeight * scalar,
			// ���
			m_pTempImageHit->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void image::setTransColor(bool trans, COLORREF transColor)
{
	m_isTransparent = trans;
	m_transColor = transColor;
}

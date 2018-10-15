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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
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
//	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
//	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
//	// 원본 DC와 호환되는 비트맵 생성
//	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
//		g_hInstance, 
//		szFileName,
//		IMAGE_BITMAP,
//		width, height,
//		LR_LOADFROMFILE);
//	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// 피격 블렌드
	m_blendFuncHit.AlphaFormat = 0;
	m_blendFuncHit.BlendFlags = 0;
	m_blendFuncHit.BlendOp = AC_SRC_OVER;

	m_pBlendImageHit = new IMAGE_INFO;
	m_pBlendImageHit->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImageHit->hBitmap = CreateCompatibleBitmap(hdc, m_pImageInfo->nWidth, m_pImageInfo->nHeight);
	m_pBlendImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pBlendImageHit->hMemDC, m_pBlendImageHit->hBitmap);
	m_pBlendImageHit->nWidth = m_pImageInfo->nWidth;
	m_pBlendImageHit->nHeight = m_pImageInfo->nHeight;

	// 브러시 색상 이미지 준비
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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pTempImageHit->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pTempImageHit->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pTempImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pTempImageHit->hMemDC, m_pTempImageHit->hBitmap);

	m_pTempImageHit->nWidth = width;
	m_pTempImageHit->nHeight = height;

	// 투명 컬러 셋팅
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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
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

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// 피격 블렌드
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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pTempImageHit->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pTempImageHit->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
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

	// 투명 컬러 셋팅
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
	if (m_isTransparent) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵을 불러올대 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,                  //복사할 장소의 DC
			0,                  //복사될 좌표 시작점 x
			0,                  //복사될 좌표 시작점 y
			m_pImageInfo->nWidth,         //복사될 이미지 가로크기
			m_pImageInfo->nHeight,         //복사될 이미지 세로크기
			
			m_pImageInfo->hMemDC,         //복사될 대상 DC
			0, 0,                  //복사 시작지점
			m_pImageInfo->nWidth,         //복사 영역 가로크기
			m_pImageInfo->nHeight,         //복사 영역 세로크기
			m_transColor               //복사할때 제외할 색상(마젠타색상 지우기)
		);
	}
	else //원본 이미지 그대로 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// 목적지
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 크기
			
			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			0, 0,					// 복사될 영역 시작좌표
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
	}
	else
	{
		// hdc : 복사될 목적지 DC
		// destX : 출력을 시작할 x 좌표
		// destY : 출력을 시작할 y 좌표
		// cx : 출력할 이미지를 어느정도까지 출력할 것인가의 가로값
		// cy : 출력할 이미지를 어느정도까지 출력할 것인가의 세로값
		// hdcSrc : 복사할 정보를 제공하는 DC
		// x1 : 이미지의 시작점을 잘라낼 것인가의 가로값
		// y1 : 이미지의 시작점을 잘라낼 것인가의 세로값
		// rop : 복사하는 옵션 (SRCCOPY)
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
		// GdiTransparentBlt : 비트맵을 불러올때 특정 색상을 제외하고 복사
		GdiTransparentBlt(
			hdc,							// 복사될 장소의 DC
			destX,							// 복사될 좌표 시작점 x
			destY,							// 복사될 좌표 시작점 y
			width,							// 복사될 이미지 가로
			height,						// 복사될 이미지 세로
			m_pImageInfo->hMemDC,		// 복사될 대상 DC
			0,								// 복사 시작 x
			0,								// 복사 시작 y
			m_pImageInfo->nWidth,			// 복사 영역 가로
			m_pImageInfo->nHeight,		// 복사 영역 세로
			m_transColor);					// 제외 색상
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
			// 목적지
			hdc,					// 복사될 목적지 DC
			destX, destY,			// 복사될 좌표 시작점
			sourWidth * scalar, sourHeight * scalar,	// 복사될 크기

			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			sourX, sourY,			// 복사될 영역 시작좌표
			sourWidth, sourHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
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
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 크기

									// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
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
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			hdc,
			destX, destY,
			SRCCOPY);
		GdiTransparentBlt(
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 크기

									// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
		AlphaBlend(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}

	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
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
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
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
			// 복사할 목표
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
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
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
		AlphaBlend(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
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
	// offset값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = m_pImageInfo->nWidth + (offsetX % m_pImageInfo->nWidth);
	if (offsetY < 0) offsetY = m_pImageInfo->nHeight + (offsetY % m_pImageInfo->nHeight);

	// 그려지는 소스의 영역(이미지)을 셋팅할 변수
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// 그려지는 DC 영역
	RECT rcDest;

	// 그려야할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	// 세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		// 소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % m_pImageInfo->nHeight;
		rcSour.bottom = m_pImageInfo->nHeight;
		sourHeight = rcSour.bottom - rcSour.top;

		// 소스 영역이 그리는 화면을 넘어갔다면(화면 밖으로 나갔을 때)
		if (y + sourHeight > drawAreaH)
		{
			// 넘어간 그림의 값만큼 바텀 값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// 그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// 가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			// 소스 영역의 가로 계산
			rcSour.left = (x + offsetX) % m_pImageInfo->nWidth;
			rcSour.right = m_pImageInfo->nWidth;
			sourWidth = rcSour.right - rcSour.left;

			// 소스 영역이 그리는 화면을 넘어가면
			if (x + sourWidth > drawAreaW)
			{
				// 넘어간 만큼 라이트 값을 왼쪽으로
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			// 그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// 그려주자
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

void image::hitRender(HDC hdc, int destX, int destY, COLORREF color)
{
	//// 브러시 색상 이미지 준비
	//HBRUSH brush = CreateSolidBrush(color);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(m_pBlendImageHit->hMemDC, brush);

	//BitBlt(
	//	// 목적지
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,

	//	// 대상
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	PATCOPY);

	//SelectObject(m_pBlendImageHit->hMemDC, oldBrush);
	//DeleteObject(brush);

	// 임시 이미지 준비
	BitBlt(
		// 목적지
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,

		// 대상
		m_pImageInfo->hMemDC,
		0, 0,
		SRCCOPY);

	// 브러시 + 임시
	BitBlt(
		// 목적지
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,

		// 대상
		m_pBlendImageHit->hMemDC,
		0, 0,
		SRCPAINT);

	if (m_isTransparent)
	{
		// 임시 이미지 출력
		GdiTransparentBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 대상
			m_pTempImageHit->hMemDC,
			0, 0,
			m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,
			m_transColor);
	}
	else
	{
		// 임시 이미지 출력
		BitBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 대상
			m_pTempImageHit->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void image::hitRender(HDC hdc, int destX, int destY, COLORREF color, int scalar)
{
	//// 브러시 색상 이미지 준비
	//HBRUSH brush = CreateSolidBrush(color);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(m_pBlendImageHit->hMemDC, brush);

	//BitBlt(
	//	// 목적지
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,

	//	// 대상
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	PATCOPY);

	//SelectObject(m_pBlendImageHit->hMemDC, oldBrush);
	//DeleteObject(brush);

	// 임시 이미지 준비
	BitBlt(
		// 목적지
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth * scalar, m_pTempImageHit->nHeight * scalar,

		// 대상
		m_pImageInfo->hMemDC,
		0, 0,
		SRCCOPY);

	// 브러시 + 임시
	BitBlt(
		// 목적지
		m_pTempImageHit->hMemDC,
		0, 0,
		m_pTempImageHit->nWidth * scalar, m_pTempImageHit->nHeight * scalar,

		// 대상
		m_pBlendImageHit->hMemDC,
		0, 0,
		SRCPAINT);

	if (m_isTransparent)
	{
		// 임시 이미지 출력
		GdiTransparentBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth * scalar, m_pImageInfo->nHeight * scalar,
			// 대상
			m_pTempImageHit->hMemDC,
			0, 0,
			m_pTempImageHit->nWidth, m_pTempImageHit->nHeight,
			m_transColor);
	}
	else
	{
		// 임시 이미지 출력
		BitBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth * scalar, m_pImageInfo->nHeight * scalar,
			// 대상
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

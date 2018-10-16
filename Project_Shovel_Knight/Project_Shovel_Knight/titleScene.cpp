#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	// 기본
	m_pBG = IMAGEMANAGER->addImage("Title_main", "image/Title/Title_main.bmp"
		, 400, 208);
	m_pSelect = IMAGEMANAGER->addImage("Title_Select", "image/Title/Title_select.bmp", 152, 8,4,1, true, RGB(255, 0, 255));
	m_pStart = IMAGEMANAGER->addImage("Title_Start", "image/Title/startgame.bmp", 158, 7, 2, 1, true, RGB(255, 0, 255));
	m_ScreenOnImg = IMAGEMANAGER->addImage("ScreenClose", "image/effect/ScreenClose.bmp", 4000, 208, 10, 1, true, RGB(255, 0, 255));

	m_fX = WINSIZEX / 2 - 90;
	m_fY = WINSIZEY / 2 + 2;

	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_nFrameCount = 0;

	m_ScreenOnFrame = 0;
	m_ScreenCount = 0;

	m_ScreenOn = false;


	m_nCurrFrameX_Start = 0;
	m_nCurrFrameY_Start = 0;
	m_nFrameCount_Start = 0;
	m_nStartCount = 0;

	m_rcSelect = RectMakeCenter(m_fX + m_pSelect->getWidth() / 2 + 20,m_fY + m_pSelect->getFrameHeight() / 2, 100, 12);
	m_rcRange = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	m_rcStart = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 2 + m_pSelect->getFrameHeight() / 2, 100, 12);
	m_rcOption = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 2 + m_pSelect->getFrameHeight() / 2 + 12, 100, 12);
	m_rcExit = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 2 + m_pSelect->getFrameHeight() / 2 + 24, 100, 12);

	m_isFlash = false;

	// 옵션 창
	m_pWindow_Option = IMAGEMANAGER->addImage("option", "image/Title/Title_Options.bmp", 308, 192, true, RGB(255, 0, 255));
	m_pSelect_Option = IMAGEMANAGER->addImage("select1", "image/Title/option_Back.bmp", 60, 20, true, RGB(255, 0, 255));

	m_fX_Option = WINSIZEX / 2 - m_pWindow_Option->getWidth() / 2 + 5;
	m_fY_Option = WINSIZEY / 2 + 2 - 60;
	m_rcBack_Option = RectMake(m_fX_Option, WINSIZEY / 2 + 2 - 60 + 30, 50, 20);
	m_rcAudio_Option = RectMake(m_fX_Option, WINSIZEY / 2 + 2 - 60 + 50, 50, 20);
	m_rcSelect_Option = RectMake(m_fX_Option, m_fY_Option + 30, 50, 20);


	// 오디오 창
	m_pWindow_Audio = IMAGEMANAGER->addImage("Audio", "image/Title/Title_Audio.bmp", 308, 192, true, RGB(255, 0, 255));
	m_pSelect_Audio = IMAGEMANAGER->addImage("back_Select", "image/Title/option_Back.bmp", 51, 20, true, RGB(255, 0, 255));
	m_pVolume_Audio = IMAGEMANAGER->addImage("audio_Volume", "image/Title/audio_Volume.bmp", 125, 18, true, RGB(255, 0, 255));

	m_fX_Audio = WINSIZEX / 2 - m_pWindow_Audio->getWidth() / 2;
	m_fY_Audio = WINSIZEY / 2 - 20;// -m_pWindow_Audio->getHeight() / 2;
	m_fMusicVolumeX_Audio = WINSIZEX / 2 + 70;
	m_fSoundVolumeX_Audio = WINSIZEX / 2 + 70;

	m_rcBack_Audio = RectMake(m_fX_Audio, m_fY_Audio, 51, 18);

	m_rcSoundVolume_Audio = RectMake(m_fX_Audio, m_fY_Audio + 18, 80, 18);
	m_rcMusicVolume_Audio = RectMake(m_fX_Audio, m_fY_Audio + 36, 80, 18);

	m_rcSelect_Audio = RectMake(m_fX_Audio+10, m_fY_Audio, 80, 20);

	m_rcSound_Audio = RectMake(m_fSoundVolumeX_Audio + 5, 109, 5, 10);
	m_rcMusic_Audio = RectMake(m_fMusicVolumeX_Audio + 5, 128, 5, 10);

	m_rcSoundRange_Audio = RectMake(m_fSoundVolumeX_Audio + 5, 109, 55, 10);

	m_isDown_Audio = false;

	m_isAudio = false;
	m_isOptions = false;

	SOUNDMANAGER->addSound("타이틀", "Sound/Main_Theme.mp3", false, false);
	SOUNDMANAGER->addSound("셀렉무브", "Sound/SelectMove.mp3", false, false);
	SOUNDMANAGER->addSound("스타트", "Sound/SelectStart.mp3", false, false);

	SOUNDMANAGER->play("타이틀", 0.8f);
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	titleUpdate();
	selectCollide();
	optionUpdate();
	audioUpdate();
}

void titleScene::render(HDC hdc)
{
	titleRender(hdc);
	optionRender(hdc);
	audioRender(hdc);
}

void titleScene::titleRender(HDC hdc)
{
	if (!m_isAudio && !m_isOptions)
	{
		m_pBG->render(hdc, 0, 0);
		//Rectangle(hdc, m_rcRange.left, m_rcRange.top, m_rcRange.right, m_rcRange.bottom);
		//Rectangle(hdc, m_rcSelect.left, m_rcSelect.top, m_rcSelect.right, m_rcSelect.bottom);
		//Rectangle(hdc, m_rcStart.left, m_rcStart.top, m_rcStart.right, m_rcStart.bottom);
		//Rectangle(hdc, m_rcOption.left, m_rcOption.top, m_rcOption.right, m_rcOption.bottom);
		//Rectangle(hdc, m_rcExit.left, m_rcExit.top, m_rcExit.right, m_rcExit.bottom);
		m_pSelect->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, m_nCurrFrameY);
		m_pStart->frameRender(hdc, WINSIZEX / 2 - 90 + 54, WINSIZEY / 2 + 2, m_nCurrFrameX_Start, m_nCurrFrameY_Start);
	
		if (m_ScreenOn) m_ScreenOnImg->frameRender(hdc, 0, 0, m_ScreenOnFrame, 0);
	}
}

void titleScene::optionRender(HDC hdc)
{
	if (m_isOptions && !m_isAudio)
	{
		m_pWindow_Option->render(hdc, WINSIZEX / 2 - m_pWindow_Option->getWidth() / 2, WINSIZEY / 2 + 2 - 60);
		//Rectangle(hdc, m_rcAudio_Option.left, m_rcAudio_Option.top, m_rcAudio_Option.right, m_rcAudio_Option.bottom);
		//Rectangle(hdc, m_rcBack_Option.left, m_rcBack_Option.top, m_rcBack_Option.right, m_rcBack_Option.bottom);
		//Rectangle(hdc, m_rcSelect_Option.left, m_rcSelect_Option.top, m_rcSelect_Option.right, m_rcSelect_Option.bottom);
		m_pSelect_Option->render(hdc, m_fX_Option,m_fY_Option + 30);
	}
}

void titleScene::audioRender(HDC hdc)
{
	if (m_isAudio && !m_isOptions)
	{
		m_pWindow_Audio->render(hdc, WINSIZEX / 2 - m_pWindow_Audio->getWidth() / 2, WINSIZEY / 2 - m_pWindow_Audio->getHeight() / 2 + 40);
		//Rectangle(hdc, m_rcSoundVolume_Audio.left, m_rcSoundVolume_Audio.top, m_rcSoundVolume_Audio.right, m_rcSoundVolume_Audio.bottom);
		//Rectangle(hdc, m_rcMusicVolume_Audio.left, m_rcMusicVolume_Audio.top, m_rcMusicVolume_Audio.right, m_rcMusicVolume_Audio.bottom);
		//Rectangle(hdc, m_rcBack_Audio.left, m_rcBack_Audio.top, m_rcBack_Audio.right, m_rcBack_Audio.bottom);
		//Rectangle(hdc, m_rcSelect_Audio.left, m_rcSelect_Audio.top, m_rcSelect_Audio.right, m_rcSelect_Audio.bottom);
		Rectangle(hdc, m_rcMusic_Audio.left, m_rcMusic_Audio.top, m_rcMusic_Audio.right, m_rcMusic_Audio.bottom);
		Rectangle(hdc, m_rcSound_Audio.left, m_rcSound_Audio.top, m_rcSound_Audio.right, m_rcSound_Audio.bottom);
		//Rectangle(hdc, m_rcSoundRange_Audio.left, m_rcSoundRange_Audio.top, m_rcSoundRange_Audio.right, m_rcSoundRange_Audio.bottom);
		if (!m_isDown_Audio)
		{
			m_pSelect_Audio->render(hdc, m_fX_Audio + 5, m_fY_Audio - 5);
		}
		else
		{
			m_pVolume_Audio->render(hdc, m_fX_Audio + 5, m_fY_Audio - 3);
		}
	}
}

void titleScene::titleUpdate()
{
	// 기본 창일때
	if (!m_isAudio && !m_isOptions)
	{
		m_nFrameCount++;
		if (m_nFrameCount % 15 == 0)
		{
			m_nCurrFrameX++;
			if (m_nCurrFrameX > 4)
			{
				m_nCurrFrameX = 0;
				m_nFrameCount = 0;
			}
		}
		if (m_isFlash)
		{
			m_nFrameCount_Start ++;
			if (m_nFrameCount_Start % 5 == 0)
			{
				m_nCurrFrameX_Start++;
				if (m_nCurrFrameX_Start > 2)
				{
					m_nStartCount++;
					m_nCurrFrameX_Start = 0;
					m_nFrameCount_Start = 0;
				}
			}
			if (m_nStartCount > 5)
			{
				m_ScreenOn = true;
				m_nStartCount = 0;
				m_isFlash = false;
			}
		}
		if (!m_isFlash)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				SOUNDMANAGER->play("셀렉무브", 0.8f);
				if (m_rcSelect.bottom < m_rcExit.bottom)
				{
					m_fX += 0.0f;
					m_fY += 12.0f;
					m_rcSelect = RectMakeCenter(m_fX + m_pSelect->getWidth() / 2 + 20, m_fY + m_pSelect->getFrameHeight() / 2, 100, 12);
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				SOUNDMANAGER->play("셀렉무브", 0.8f);
				if (m_rcSelect.top > m_rcStart.top)
				{
					m_fX += 0.0f;
					m_fY -= 12.0f;
					m_rcSelect = RectMakeCenter(m_fX + m_pSelect->getWidth() / 2 + 20, m_fY + m_pSelect->getFrameHeight() / 2, 100, 12);
				}
			}
		}
	}

	if (m_ScreenOn) {
		m_ScreenCount++;

		if (m_ScreenCount % 7 == 0) {
			m_ScreenOnFrame++;
			m_ScreenOnImg->setFrameX(m_ScreenOnFrame);

			if (m_ScreenOnFrame >= 10) {
				m_ScreenOnFrame = 10;
				m_ScreenCount = 0;
				SCENEMANAGER->changeScene("PlayScene");
				m_ScreenOn = false;
			}
		}
	}
}

void titleScene::optionUpdate()
{
	if (m_isOptions && !m_isAudio)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && m_rcSelect_Option.bottom < m_rcAudio_Option.bottom)
		{
			m_fX_Option += 0.0f;
			m_fY_Option += 20.0f;
			m_rcSelect_Option = RectMake(m_fX_Option, m_fY_Option +30, 50, 20);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP) && m_rcSelect_Option.top > m_rcBack_Option.top)
		{
			m_fX_Option += 0.0f;
			m_fY_Option -= 20.0f;
			m_rcSelect_Option = RectMake(m_fX_Option, m_fY_Option + 30, 50, 20);
		}
	}
	optionCollide();
}

void titleScene::audioUpdate()
{
	if (m_isAudio && !m_isOptions)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			SOUNDMANAGER->play("셀렉무브", 0.8f);
			if (m_rcSelect_Audio.bottom < m_rcMusicVolume_Audio.bottom)
			{
				m_fX_Audio += 0.0f;
				m_fY_Audio += 18.0f;
				m_rcSelect_Audio = RectMake(m_fX_Audio, m_fY_Audio, 80, 20);
				m_isDown_Audio = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			SOUNDMANAGER->play("셀렉무브", 0.8f);
			if (m_rcSelect_Audio.top > m_rcBack_Audio.top)
			{
				m_fX_Audio += 0.0f;
				m_fY_Audio -= 18.0f;
				m_rcSelect_Audio = RectMake(m_fX_Audio, m_fY_Audio, 80, 20);
			}
		}
	}
	audioCollide();
}

void titleScene::selectCollide()
{
	if (!m_isAudio && !m_isOptions)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_rcSelect, &m_rcStart))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SOUNDMANAGER->play("스타트", 0.8f);
				SOUNDMANAGER->stop("타이틀");
				//m_ScreenOn = true;
				m_isFlash = true;
			}
		}
		else if (IntersectRect(&rc, &m_rcSelect, &m_rcOption))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//SCENEMANAGER->changeScene("optionScene");
				m_isOptions = true;
			}
		}
		else if (IntersectRect(&rc, &m_rcSelect, &m_rcExit))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				PostQuitMessage(0);
			}
		}
	}
}

void titleScene::optionCollide()
{
	if (m_isOptions && !m_isAudio)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_rcBack_Option, &m_rcSelect_Option))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//SCENEMANAGER->changeScene("title");
				m_isOptions = false;
				m_isAudio = false;
			}
		}
		if (IntersectRect(&rc, &m_rcAudio_Option, &m_rcSelect_Option))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//SCENEMANAGER->changeScene("audioScene");
				m_isAudio = true;
				m_isOptions = false;
			}
		}
	}
}

void titleScene::audioCollide()
{
	if (m_isAudio && !m_isOptions)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_rcBack_Audio, &m_rcSelect_Audio))
		{
			m_isDown_Audio = false;
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//SCENEMANAGER->changeScene("optionScene");
				m_isOptions = true;
				m_isAudio = false;
			}
		}
		if (IntersectRect(&rc, &m_rcSoundVolume_Audio, &m_rcSelect_Audio))
		{

			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && m_rcSound_Audio.right < m_rcSoundRange_Audio.right)
			{
				m_fSoundVolumeX_Audio += 5.0f;
				m_rcSound_Audio = RectMake(m_fSoundVolumeX_Audio + 5, 109, 5, 10);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && m_rcSound_Audio.left > m_rcSoundRange_Audio.left)
			{
				m_fSoundVolumeX_Audio -= 5.0f;
				m_rcSound_Audio = RectMake(m_fSoundVolumeX_Audio + 5, 109, 5, 10);
			}
		}
		if (IntersectRect(&rc, &m_rcMusicVolume_Audio, &m_rcSelect_Audio))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && m_rcMusic_Audio.right < m_rcSoundRange_Audio.right)
			{
				m_fMusicVolumeX_Audio += 5.0f;
				m_rcMusic_Audio = RectMake(m_fMusicVolumeX_Audio + 5, 128, 5, 10);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && m_rcMusic_Audio.left > m_rcSoundRange_Audio.left)
			{
				m_fMusicVolumeX_Audio -= 5.0f;
				m_rcMusic_Audio = RectMake(m_fMusicVolumeX_Audio + 5, 128, 5, 10);
			}
		}
	}
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}

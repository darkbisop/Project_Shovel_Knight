#pragma once
#include "scene.h"

class titleScene : public scene
{
private:
	// 기본 화면
	image * m_pBG;
	image*	m_pSelect;
	image*	m_pStart;

	image*	m_ScreenOnImg;

	RECT	m_rcStart;
	RECT	m_rcOption;
	RECT	m_rcExit;
	RECT	m_rcSelect;
	RECT	m_rcRange;

	float	m_fX;
	float	m_fY;

	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nFrameCount;
	int		m_nStartCount;
	int		m_ScreenCount;

	int		m_nCurrFrameX_Start;
	int		m_nCurrFrameY_Start;
	int		m_nFrameCount_Start;

	int		m_ScreenOnFrame;


	bool	m_ScreenOn;
	

	// 옵션 창
	image*	m_pWindow_Option;
	image*	m_pSelect_Option;

	RECT	m_rcSelect_Option;

	RECT	m_rcBack_Option;
	RECT	m_rcAudio_Option;

	float	m_fX_Option;
	float	m_fY_Option;

	// 오디오 창 이미지
	image*	m_pWindow_Audio;
	image*	m_pSelect_Audio;
	image*	m_pVolume_Audio;

	RECT	m_rcSelect_Audio;
	RECT	m_rcBack_Audio;
	RECT	m_rcSoundVolume_Audio;
	RECT	m_rcMusicVolume_Audio;
	RECT	m_rcSound_Audio;
	RECT	m_rcMusic_Audio;

	RECT	m_rcSoundRange_Audio;

	float	m_fMusicVolumeX_Audio;
	float	m_fSoundVolumeX_Audio;

	float	m_fX_Audio;
	float	m_fY_Audio;

	bool	m_isDown_Audio;
	bool	m_isFlash;

	// 옵션 or 오디오
	bool	m_isOptions;
	bool	m_isAudio;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void titleRender(HDC hdc);
	void optionRender(HDC hdc);
	void audioRender(HDC hdc);

	void titleUpdate();
	void optionUpdate();
	void audioUpdate();

	void selectCollide();
	void optionCollide();
	void audioCollide();

	titleScene();
	~titleScene();
};


#pragma once

class PlayScene;
class titleScene;
class TestScene;

class mainGame
{
private:
	// DC
	HDC hdc;

	// �����
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	PlayScene*		m_PlayScene;
	titleScene*		m_titleScene;
	TestScene*		m_TestScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};


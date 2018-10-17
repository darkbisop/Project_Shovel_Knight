#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

HRESULT TestScene::init()
{
	IMAGEMANAGER->addImage("산", "image/맵.bmp", 400, 208, true, RGB(255, 0, 255));
	BG = IMAGEMANAGER->addImage("템프배경", "image/mapImage.bmp", 400, 208, true, RGB(255, 0, 255));

	m_IdleImg = IMAGEMANAGER->addImage("Player_Idle", "image/Player/Player_Idle.bmp", 34, 64, 1, 2, true, RGB(255, 0, 255));
	m_MoveImg = IMAGEMANAGER->addImage("Player_move", "image/Player/Player_move.bmp", 240, 70, 6, 2, true, RGB(255, 0, 255));
	m_AttackImg = IMAGEMANAGER->addImage("Player_attack", "image/Player/Player_attack.bmp", 270, 70, 5, 2, true, RGB(255, 0, 255));
	m_JumpImg = IMAGEMANAGER->addImage("Player_jump", "image/Player/Player_jump.bmp", 31, 68, 1, 2, true, RGB(255, 0, 255));
	m_AttackDownImg = IMAGEMANAGER->addImage("Player_AttackDown", "image/Player/Player_AttackDown.bmp", 24, 72, 1, 2, true, RGB(255, 0, 255));
	m_JumpDown = IMAGEMANAGER->addImage("Player_JumpDown", "image/Player/Player_JumpDown.bmp", 33, 68, 1, 2, true, RGB(255, 0, 255));
	
	m_fX = 30;
	m_fY = 60;
	m_fSpeed = 2.0f;
	jumpSpeed = 0;
	gravity = 0;
	
	m_FrameCount = 0;
	m_CurrFrameX = 0;
	m_CurrFrameY = 0;
	m_AtkFrameCount = 0;
	m_AttackCount = 0;
	

	m_isRight = true;
	m_isAttack = false;
	m_isGround = false;
	m_isFalling = false;
	m_State = TempIdle;

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	m_FrameCount++;
	Colliosion();
	KeyProcess();
	Animation();
	

	if (m_isGround == false) {
		gravity += 0.3f;
		m_fY -= jumpSpeed - gravity;
	}

	if (KEYMANAGER->isOnceKeyDown('1')) SCENEMANAGER->changeScene("titleScene");
	

	m_rc = RectMake(m_fX + 5, m_fY, 20, 25);

	/*if (m_State == TempDownATK) m_AttackDownRc = RectMake(m_fX + 7, m_fY + 20, 16, 10);
	else  m_AttackDownRc = RectMake(-1000, -1000, -1, -1);*/
}

void TestScene::render(HDC hdc)
{
	BG->render(hdc, 0, 0);
	IMAGEMANAGER->findImage("산")->render(hdc);
	SetDCBrushColor(IMAGEMANAGER->findImage("산")->getMemDC(), (RGB(255, 0, 255)));
	SelectObject(IMAGEMANAGER->findImage("산")->getMemDC(), GetStockObject(DC_BRUSH));
	SelectObject(IMAGEMANAGER->findImage("산")->getMemDC(), GetStockObject(NULL_PEN));
	Ellipse(IMAGEMANAGER->findImage("산")->getMemDC(), m_AttackRc.left, m_AttackRc.top, m_AttackRc.right, m_AttackRc.bottom);
	ShovelRender(hdc);
}

void TestScene::KeyProcess()
{

	
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			if (m_State != TempJump && m_State != TempMove && m_State != TempDownATK) {
				m_State = TempAttack;
			}
			if (m_State != TempJump && m_State != TempDownATK) {
				m_State = TempMove;
			}

			m_fX += m_fSpeed;

			m_isRight = true;
		}

		else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (m_State != TempJump && m_State != TempMove && m_State != TempDownATK) {
				m_State = TempAttack;
			}
			if (m_State != TempJump && m_State != TempDownATK) {
				m_State = TempMove;
			}

			m_fX -= m_fSpeed;
			m_isRight = false;
		}
	
	if (KEYMANAGER->isOnceKeyDown('C') && m_isGround == true) {
		jumpSpeed += 6.5f;
		if (jumpSpeed > 0.1f) {
			m_State = TempJump;
			m_isGround = false;
		}
	}

	if (jumpSpeed > 1.0f && KEYMANAGER->isStayKeyDown(VK_DOWN) || gravity > 0.1f && KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		m_State = TempDownATK;
		m_AttackDownRc = RectMake(m_fX + 7, m_fY + 20, 17, 10);
	}

	if (KEYMANAGER->isOnceKeyDown('X')) {
		SOUNDMANAGER->play("플레이어공격", 1.0f);
		m_State = TempAttack;
		m_isAttack = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) m_State = TempIdle;
}

void TestScene::Animation()
{
	if (m_State == TempMove && m_isRight == true) {
		m_FrameCount++;

		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX++;
			m_MoveImg->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX > m_MoveImg->getMaxFrameX()) {
				m_CurrFrameX = 0;
			}
		}
	}

	else if (m_State == TempMove && m_isRight == false) {
		m_FrameCount++;
		m_CurrFrameY = 1;
		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX++;
			m_MoveImg->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX > m_MoveImg->getMaxFrameX()) {
				m_CurrFrameX = 0;
			}
		}
	}

	if (m_isAttack) {
		m_State = TempAttack;
		if (m_isRight == true) {
			m_CurrFrameY = 0;
			m_AttackCount++;
			m_FrameCount++;

			if (m_AttackCount > 10) {
				m_AttackRc = RectMake(m_fX + 35, m_fY - 5, 30, 30);
			}
			if (m_AttackCount > 11) {
				m_AttackRc = RectMake(-1000, -1000, -1, -1);
			}

			if (m_FrameCount % 5 == 0) {
				m_AtkFrameCount++;
				m_AttackImg->setFrameX(m_AtkFrameCount);

				if (m_AtkFrameCount > m_AttackImg->getMaxFrameX()) {
					m_AtkFrameCount = 0;
					m_AttackCount = 0;
					m_isAttack = false;
					m_State = TempIdle;
				}
			}
		}
	}
}

void TestScene::ShovelRender(HDC hdc)
{
	if (m_State == TempIdle) {
			if (m_isRight) m_IdleImg->frameRender(hdc, m_fX, m_fY - 8, 0, 0);
			else if (!m_isRight) m_IdleImg->frameRender(hdc, m_fX - 2, m_fY - 8, 0, 1);
		
	}

	else if (m_State == TempMove) {
	
			if (m_isRight) m_MoveImg->frameRender(hdc, m_fX, m_fY - 11, m_CurrFrameX, 0);
			else if (!m_isRight) m_MoveImg->frameRender(hdc, m_fX - 8, m_fY - 11, m_CurrFrameX, 1);
		
	}

	else if (m_isAttack) {
	
			if (m_isRight) m_AttackImg->frameRender(hdc, m_fX, m_fY - 9, m_AtkFrameCount, m_CurrFrameY);
			else if (!m_isRight) m_AttackImg->frameRender(hdc, m_fX - 19, m_fY - 9, m_AtkFrameCount, m_CurrFrameY);
		

	}

	else if (m_State == TempJump) {
		
			if (m_isRight) {
				if (jumpSpeed - gravity >= 0)m_JumpImg->frameRender(hdc, m_fX - 3, m_fY - 8, 0, 0);
				else if (jumpSpeed - gravity <= 0) m_JumpDown->frameRender(hdc, m_fX, m_fY - 8, 0, 0);
			}
			else if (!m_isRight) {
				if (jumpSpeed - gravity >= 0)m_JumpImg->frameRender(hdc, m_fX, m_fY - 8, 0, 1);
				else if (jumpSpeed - gravity <= 0) m_JumpDown->frameRender(hdc, m_fX - 3, m_fY - 8, 0, 1);
			}
		
	}

	else if (m_State == TempDownATK) {
		
			if (m_isRight) m_AttackDownImg->frameRender(hdc, m_fX + 2, m_fY - 8, 0, 0);
			else if (!m_isRight) m_AttackDownImg->frameRender(hdc, m_fX + 2, m_fY - 8, 0, 1);
		
	}
}

void TestScene::Colliosion()
{
	if (m_isGround == false) {

		COLORREF color = GetPixel(IMAGEMANAGER->findImage("산")->getMemDC(), m_fX, m_fY + 23);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			m_fY = m_fY - 5;
			m_isGround = true;
			gravity = 0;
			jumpSpeed = 0;
			m_State = TempIdle;
		}
	}

	if (m_isGround == true) {

		COLORREF color = GetPixel(IMAGEMANAGER->findImage("산")->getMemDC(), (int)m_fX, (int)m_fY + 23);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 0))
		{
			gravity += 9.8f / 60.0f;
			m_fY -= jumpSpeed - gravity;;
		}
	}

	if (m_State == TempMove && m_isRight)
	{
		for (int i = m_fY - 10; i < m_fY + 10; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("산")->getMemDC(), m_fX + 30, m_fY);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				m_fX = m_fX - 1;
			}
		}

	}

	
}



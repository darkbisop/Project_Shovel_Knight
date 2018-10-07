#include "stdafx.h"
#include "Player.h"


HRESULT Player::init()
{
	m_IdleImg = IMAGEMANAGER->addImage("Player_Idle", "image/Player/Player_Idle.bmp", 34, 64, 1, 2, true, RGB(255, 0, 255));
	m_MoveImg = IMAGEMANAGER->addImage("Player_move", "image/Player/Player_move.bmp", 240, 70, 6, 2, true, RGB(255, 0, 255));
	m_AttackImg = IMAGEMANAGER->addImage("Player_attack", "image/Player/Player_attack.bmp", 270, 70, 5, 2, true, RGB(255, 0, 255));
	m_JumpImg = IMAGEMANAGER->addImage("Player_jump", "image/Player/Player_jump.bmp", 31, 68, 1, 2, true, RGB(255, 0, 255));
	m_AttackDownImg = IMAGEMANAGER->addImage("Player_AttackDown", "image/Player/Player_AttackDown.bmp", 24, 72, 1, 2, true, RGB(255, 0, 255));
	m_JumpDown = IMAGEMANAGER->addImage("Player_JumpDown", "image/Player/Player_JumpDown.bmp", 33, 68, 1, 2, true, RGB(255, 0, 255));
	m_LadderUpImg = IMAGEMANAGER->addImage("Player_ladder", "image/Player/Player_ladder.bmp", 100, 32, 4, 1, true, RGB(255, 0, 255));
	m_DamagedImg = IMAGEMANAGER->addImage("Player_damaged", "image/Player/Player_damaged.bmp", 35, 78, 1, 2, true, RGB(255, 0, 255));
	m_AppearImg = IMAGEMANAGER->addImage("Player_appear", "image/Player/Player_appear.bmp", 540, 51, 9, 1, true, RGB(255, 0, 255));

	m_UI = IMAGEMANAGER->addImage("UI", "image/UI.bmp", 400, 18, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("플레이어등장", "Sound/Player_Appear.mp3", false, false);
	SOUNDMANAGER->addSound("플레이어점프", "Sound/JumpSFX.mp3", false, false);
	SOUNDMANAGER->addSound("플레이어공격", "Sound/AttackSFX.mp3", false, false);
	SOUNDMANAGER->addSound("플레이어착지", "Sound/LandingSFX.mp3", false, false);

	m_inventory = new Inventory;
	m_inventory->init();

	m_Equipment = new Equipment;
	m_Equipment->init();

	m_inventory->SetEquipmentLink(m_Equipment);
	m_Equipment->setInventoryLink(m_inventory);

	m_fX = -35;
	m_fY = 790;
	m_fSpeed = 2.0f;
	jumpSpeed = 0;
	gravity = 0;
	Money = 10000;
	
	m_FrameCount = 0;
	m_CurrFrameX = 0;
	m_CurrFrameY = 0;
	m_AtkFrameCount = 0;
	m_AttackCount = 0;
	m_invincibleCount = 100;
	m_invincibleAlpha = 0;
	m_DamagedTime = 0;
	m_AppearTime = 0;

	m_isRight = true;
	m_isAttack = false;
	m_isGround = false;
	m_invincibleTime = false;
	m_isDamaged = false;
	m_isAppear = false;

	m_State = P_IDLE;
	
	return S_OK;
}

void Player::release()
{
	m_inventory->release();
	SAFE_DELETE(m_inventory);

	m_Equipment->release();
	SAFE_DELETE(m_Equipment);
}

void Player::update()
{
	m_FrameCount++;
	m_inventory->update();
	m_Equipment->update();

	KeyProcess();
	Animation();

	if (m_isGround == false) {
		gravity += 0.3f;
		m_fY -= jumpSpeed - gravity;
	}

	m_rc = RectMake(m_fX + 5, m_fY, 20, 25);

	if (m_State == P_DOWNATTACK) m_AttackDownRc = RectMake(m_fX + 7, m_fY + 20, 10, 10);
	else  m_AttackDownRc = RectMake(-1000, -1000, -1, -1);
}

void Player::render(HDC hdc)
{
	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//Rectangle(hdc, m_AttackRc.left, m_AttackRc.top, m_AttackRc.right, m_AttackRc.bottom);
	//Rectangle(hdc, m_AttackDownRc.left, m_AttackDownRc.top, m_AttackDownRc.right, m_AttackDownRc.bottom);

	ShovelRender(hdc);

	m_UI->render(hdc, MAPMANAGER->getCamera().x, MAPMANAGER->getCamera().y);
	m_inventory->render(hdc);
	m_Equipment->render(m_UI->getMemDC());

	char str[64];
	//wsprintf(str, "money : %d", m_AppearTime);
	sprintf_s(str, "x : %f, y : %f", m_fX, m_fY);
	TextOut(hdc, m_fX, m_fY - 20, str, strlen(str));
}

void Player::KeyProcess()
{
	if (m_State != P_LADDERUP) {
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			if (m_State != P_JUMP && m_State != P_MOVE && m_State != P_DOWNATTACK) {
				m_State = P_ATTACK;
			}
			if (m_State != P_JUMP && m_State != P_DOWNATTACK) {
				m_State = P_MOVE;
			}

			m_fX += m_fSpeed;
			m_isRight = true;
		}

		else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (m_State != P_JUMP && m_State != P_MOVE && m_State != P_DOWNATTACK) {
				m_State = P_ATTACK;
			}

			if (m_State != P_JUMP && m_State != P_DOWNATTACK) {
				m_State = P_MOVE;
			}

			m_fX -= m_fSpeed;
			m_isRight = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('C') && gravity <= 0) {
		SOUNDMANAGER->play("플레이어점프", 1.0f);
		jumpSpeed += 7.0f;
		if (jumpSpeed > 0.1f) {
			m_State = P_JUMP;
			m_isGround = false;
		}
	}

	if (jumpSpeed > 1.0f && KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		m_State = P_DOWNATTACK;
		m_AttackDownRc = RectMake(m_fX + 7, m_fY + 20, 10, 10);
	}

	if (KEYMANAGER->isOnceKeyDown('X')) {
		SOUNDMANAGER->play("플레이어공격", 1.0f);
		m_State = P_ATTACK;
		m_isAttack = true;
	}
	

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && m_isRight == true) {
		m_State = P_IDLE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_isRight == false) {
		m_State = P_IDLE;
	}
}

void Player::Animation()
{
	if (m_isAppear) {
		m_AppearTime++;
		m_State = P_APPEAR;
		if (!SOUNDMANAGER->isPlaySound("플레이어등장")) {
			SOUNDMANAGER->play("플레이어등장");
		}
		if (m_AppearTime < 30) {

			m_fX -= cosf(10) * 6.0f;
			m_fY -= sinf(40) * 6.0f;
		}
		else if (m_AppearTime >= 110) {
			m_isAppear = false;
			m_AppearTime = 0;
			SOUNDMANAGER->play("게임배경음", 0.9f);
		}
	}

	if (m_State == P_MOVE && m_isRight == true) {
		m_FrameCount++;
		
		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX++;
			m_MoveImg->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX > m_MoveImg->getMaxFrameX()) {
				m_CurrFrameX = 0;
			}
		}
	}

	else if (m_State == P_MOVE && m_isRight == false) {
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
		m_State = P_ATTACK;
		if (m_isRight == true) {
			m_CurrFrameY = 0;
			m_AttackCount++;
			m_FrameCount++;

			if (m_AttackCount > 10) {
				m_AttackRc = RectMake(m_fX + 35, m_fY + 10 , 10, 10);
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
					m_State = P_IDLE;
				}
			}
		}
		else if (m_isRight == false) {
			m_CurrFrameY = 1;
			m_FrameCount++;
			m_AttackCount++;

			if (m_AttackCount > 10) {
				m_AttackRc = RectMake(m_fX - 10, m_fY + 10, 10, 10);
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
					m_State = P_IDLE;
				}
			}
		}
	}

	else if (m_State == P_LADDERUP) {
		m_FrameCount++;
		if (m_FrameCount % 9 == 0) {
			m_CurrFrameX++;
			m_LadderUpImg->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX >= 3) {
				m_CurrFrameX = 0;
			}
		}
	}

	else if (m_State == P_APPEAR) {
		m_FrameCount++;
		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX++;
			m_AppearImg->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX >= 8) {
				m_CurrFrameX = 8;
			}
		}
	}

	if (m_isDamaged == true) {
		m_State = P_DAMAGED;
		m_DamagedTime++;
		if (m_DamagedTime < 17) {
			m_fX += cosf(10) * 4.0f;
			m_fY -= sinf(40) * 4.0f;
		}

		else if (m_DamagedTime >= 18) {
			m_State = P_IDLE;
			m_DamagedTime = 0;
			m_isDamaged = false;
		}
	}
	

	if (m_invincibleTime == true) {
		m_invincibleCount--;
		if (m_invincibleCount >= 0) {
			if (m_invincibleAlpha <= 255) {
				m_invincibleAlpha += 80;
			}

			if (m_invincibleAlpha >= 255) {
				m_invincibleAlpha = 0;
			}
		}
		else if (m_invincibleCount <= 0) {
			m_invincibleTime = false;
			m_invincibleCount = 100;
		}
	}
}

void Player::ShovelRender(HDC hdc)
{
	if (m_State == P_IDLE) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_IdleImg->frameAlphaRender(hdc, m_fX, m_fY - 7, 0, 0, m_invincibleAlpha);
			else if (!m_isRight) m_IdleImg->frameAlphaRender(hdc, m_fX - 2, m_fY - 7, 0, 1, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_IdleImg->frameRender(hdc, m_fX, m_fY - 7, 0, 0);
			else if (!m_isRight) m_IdleImg->frameRender(hdc, m_fX - 2, m_fY - 7, 0, 1);
		}
	}
	
	else if (m_State == P_MOVE) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_MoveImg->frameAlphaRender(hdc, m_fX, m_fY - 10, m_CurrFrameX, 0, m_invincibleAlpha);
			else if (!m_isRight) m_MoveImg->frameAlphaRender(hdc, m_fX - 8, m_fY - 10, m_CurrFrameX, 1, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_MoveImg->frameRender(hdc, m_fX, m_fY - 10, m_CurrFrameX, 0);
			else if (!m_isRight) m_MoveImg->frameRender(hdc, m_fX - 8, m_fY - 10, m_CurrFrameX, 1);
		}
	}
	
	else if (m_isAttack) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_AttackImg->frameAlphaRender(hdc, m_fX, m_fY - 7, m_AtkFrameCount, m_CurrFrameY, m_invincibleAlpha);
			else if (!m_isRight) m_AttackImg->frameAlphaRender(hdc, m_fX - 19, m_fY - 7, m_AtkFrameCount, m_CurrFrameY, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_AttackImg->frameRender(hdc, m_fX, m_fY - 7, m_AtkFrameCount, m_CurrFrameY);
			else if (!m_isRight) m_AttackImg->frameRender(hdc, m_fX - 19, m_fY - 7, m_AtkFrameCount, m_CurrFrameY);
		}
		
	}

	else if (m_State == P_JUMP) {
		if (m_invincibleTime == true) {
			if (m_isRight) {
				if (jumpSpeed - gravity >= 0)m_JumpImg->frameAlphaRender(hdc, m_fX - 3, m_fY - 8, 0, 0, m_invincibleAlpha);
				else if (jumpSpeed - gravity <= 0) m_JumpDown->frameAlphaRender(hdc, m_fX, m_fY - 8, 0, 0, m_invincibleAlpha);
			}
			else if (!m_isRight) {
				if (jumpSpeed - gravity >= 0)m_JumpImg->frameAlphaRender(hdc, m_fX, m_fY - 8, 0, 1, m_invincibleAlpha);
				else if (jumpSpeed - gravity <= 0) m_JumpDown->frameAlphaRender(hdc, m_fX - 3, m_fY - 8, 0, 1, m_invincibleAlpha);
			}
		}
		else {
			if (m_isRight) {
				if (jumpSpeed - gravity >= 0)m_JumpImg->frameRender(hdc, m_fX - 3, m_fY - 8, 0, 0);
				else if (jumpSpeed - gravity <= 0) m_JumpDown->frameRender(hdc, m_fX, m_fY - 8, 0, 0);
			}
			else if (!m_isRight) {
				if (jumpSpeed - gravity >= 0)m_JumpImg->frameRender(hdc, m_fX, m_fY - 8, 0, 1);
				else if (jumpSpeed - gravity <= 0) m_JumpDown->frameRender(hdc, m_fX - 3, m_fY - 8, 0, 1);
			}
		}
	}

	else if (m_State == P_DOWNATTACK) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_AttackDownImg->frameAlphaRender(hdc, m_fX + 2, m_fY - 8, 0, 0, m_invincibleAlpha);
			else if (!m_isRight) m_AttackDownImg->frameAlphaRender(hdc, m_fX + 2, m_fY - 8, 0, 1, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_AttackDownImg->frameRender(hdc, m_fX + 2, m_fY - 8, 0, 0);
			else if (!m_isRight) m_AttackDownImg->frameRender(hdc, m_fX + 2, m_fY - 8, 0, 1);
		}
	}

	else if (m_State == P_DAMAGED) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_DamagedImg->frameAlphaRender(hdc, m_fX - 3, m_fY - 14, 0, 0, m_invincibleAlpha);
			else if (!m_isRight) m_DamagedImg->frameAlphaRender(hdc, m_fX - 3, m_fY - 14, 0, 1, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_DamagedImg->frameRender(hdc, m_fX - 3, m_fY - 14, 0, 0);
			else if (!m_isRight) m_DamagedImg->frameRender(hdc, m_fX - 3, m_fY - 14, 0, 1);
		}
	}

	else if (m_State == P_LADDERUP) {
		m_LadderUpImg->frameRender(hdc, m_fX + 3, m_fY - 10, m_CurrFrameX, 0);
	}

	else if (m_State == P_LADDERSTOP) {
		m_LadderUpImg->frameRender(hdc, m_fX + 5, m_fY - 10, 0, 0);
	}

	else if (m_State == P_APPEAR) {
		m_AppearImg->frameRender(hdc, m_fX - 22, m_fY - 23, m_CurrFrameX, 0);
	}
}

void Player::RectColliosion(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_rc, &x)) {

		if (m_rc.right  < x.left + 4) {
			m_fX -= 2.0f;
			m_State = P_IDLE;
		}

		else if (m_rc.left > x.right - 4) {
			m_fX += 2.0f;
			m_State = P_IDLE;
		}

		else if (m_rc.bottom > x.bottom ) {
			gravity = 0;
			jumpSpeed = 0;
			m_isGround = false;
			m_fY += 2.0f;
		}
		else /*if (m_rc.bottom > x.top)*/ {
			/*if (!SOUNDMANAGER->isPlaySound("플레이어착지") && m_State == P_JUMP) {
				SOUNDMANAGER->play("플레이어착지", 1.0f);
			}*/
			m_State = P_IDLE;
			m_fY = x.top - 24;
			gravity = 0;
			jumpSpeed = 0;
			m_isGround = true;
		}
	}

	else m_isGround = false;
}

void Player::LadderColliosion(RECT x)
{
	RECT rc;
	if (m_State != P_JUMP) {
		if (IntersectRect(&rc, &m_rc, &x)) {
			gravity = 0;
			jumpSpeed = 0;
			m_isGround = true;
			
			if (KEYMANAGER->isStayKeyDown(VK_UP)) {
				m_State = P_LADDERUP;
				m_fX = x.left - 12;
				m_fY -= 1.0f;
			}

			else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
				m_State = P_LADDERUP;
				m_fX = x.left - 12;
				m_fY += 1.0f;
			} 
			else m_State = P_LADDERSTOP;
		}
	}
}

void Player::DownATKCollision(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_AttackDownRc, &x)) {
		if (m_AttackDownRc.bottom > x.top - 20) {
			gravity = 0;
			jumpSpeed += 0.1f;
			if (jumpSpeed > 0.1f) {
				m_isGround = false;
			}
		}
	
	}
}

Player::Player() : Money(10000)
{
}


Player::~Player()
{
}

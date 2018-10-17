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
	m_DeathImg = IMAGEMANAGER->addImage("PlayerDeath", "image/Player/PlayerDeath.bmp", 333, 34, 9, 1, true, RGB(255, 0, 255));
	m_HpBar1 = IMAGEMANAGER->addImage("PlayerHP", "image/Player/PlayerHP.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_HpBar2 = IMAGEMANAGER->addImage("PlayerHP", "image/Player/PlayerHP.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_HpBar3 = IMAGEMANAGER->addImage("PlayerHP", "image/Player/PlayerHP.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_HpBar4 = IMAGEMANAGER->addImage("PlayerHP", "image/Player/PlayerHP.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_HpBar5 = IMAGEMANAGER->addImage("PlayerHP", "image/Player/PlayerHP.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_HpKAn = IMAGEMANAGER->addImage("HPKAN", "image/Player/HPKAN.bmp", 8, 8, 1, 1, true, RGB(255, 0, 255));

	m_Number_1 = IMAGEMANAGER->addImage("Number", "image/Number.bmp", 70, 7, 10, 1, true, RGB(255, 0, 255));
	m_Number_2 = IMAGEMANAGER->addImage("Number", "image/Number.bmp", 70, 7, 10, 1, true, RGB(255, 0, 255));
	m_Number_3 = IMAGEMANAGER->addImage("Number", "image/Number.bmp", 70, 7, 10, 1, true, RGB(255, 0, 255));
	m_Number_4 = IMAGEMANAGER->addImage("Number", "image/Number.bmp", 70, 7, 10, 1, true, RGB(255, 0, 255));

	m_UI = IMAGEMANAGER->addImage("UI", "image/UI.bmp", 400, 18, true, RGB(255, 0, 255));

	
	
	m_inventory = new Inventory;
	m_inventory->init();

	m_Equipment = new Equipment;
	m_Equipment->init();

	m_inventory->SetEquipmentLink(m_Equipment);
	m_Equipment->setInventoryLink(m_inventory);

	m_fX = 192;
	m_fY = 183;
	/*m_fX = -35;
	m_fY = 790;*/
	Hp = 8;
	Mana = 40;
	m_fSpeed = 2.0f;
	jumpSpeed = 0;
	gravity = 0;
	Money = 9000;

	m_FrameCount = 0;
	m_CurrFrameX = 0;
	m_CurrFrameY = 0;
	m_AtkFrameCount = 0;
	m_AttackCount = 0;
	m_invincibleCount = 100;
	m_invincibleAlpha = 0;
	m_DamagedTime = 0;
	m_AppearTime = 0;
	m_DEADCount = 0;

	m_isRight = true;
	m_isAttack = false;
	m_isGround = false;
	m_invincibleTime = false;
	m_isDamaged = false;
	m_isAppear = false;
	m_isFalling = false;
	m_isDead = false;
	m_isCheck = false;

	m_isMovingMap = false;
	m_isAfterLoad = false;
	m_isDeadCHeck = false;
	m_isFireLeft = false;
	m_EquipFlameWand = false;
	m_isPlusHp = false;

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
	FireBallMove();


	if (KEYMANAGER->isOnceKeyDown('1')) Hp--;
	if (KEYMANAGER->isOnceKeyDown('2')) {
		m_isPlusHp = true;
		Hp = 10;
	}

	if (m_isMovingMap == false) {
		if (m_isGround == false) {

			gravity += 0.3f;
			m_fY -= jumpSpeed - gravity;
		}
	}

	m_rc = RectMake(m_fX + 5, m_fY, 20, 25);

	if (m_State == P_DOWNATTACK) m_AttackDownRc = RectMake(m_fX + 7, m_fY + 20, 16, 10);
	else  m_AttackDownRc = RectMake(-1000, -1000, -1, -1);
}

void Player::render(HDC hdc)
{
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	Rectangle(hdc, m_AttackRc.left, m_AttackRc.top, m_AttackRc.right, m_AttackRc.bottom);
	//Rectangle(hdc, m_AttackDownRc.left, m_AttackDownRc.top, m_AttackDownRc.right, m_AttackDownRc.bottom);

	ShovelRender(hdc);

	m_UI->render(hdc, MAPMANAGER->getCamera().x, MAPMANAGER->getCamera().y);
	m_inventory->render(hdc);
	m_Equipment->render(m_UI->getMemDC());

	UIrender(hdc);

	//SetTextColor(hdc, RGB(255, 255, 255));
	//SetBkColor(hdc, RGB(255, 0, 255));
	char str[64];
	wsprintf(str, "%d", Hp);
	//sprintf_s(str, "x : %f, y : %f", m_fX, m_fY);
	TextOut(hdc, m_fX - 100, m_fY, str, strlen(str));
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

			if (m_isMovingMap == false) {
				m_fX += m_fSpeed;

				m_isRight = true;
			}
		}

		else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (m_State != P_JUMP && m_State != P_MOVE && m_State != P_DOWNATTACK) {
				m_State = P_ATTACK;
			}

			if (m_State != P_JUMP && m_State != P_DOWNATTACK) {
				m_State = P_MOVE;
			}

			if (m_isMovingMap == false)m_fX -= m_fSpeed;
			m_isRight = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('C') && gravity <= 0) {
		SOUNDMANAGER->play("플레이어점프", 1.0f);
		jumpSpeed += 6.5f;
		if (jumpSpeed > 0.1f) {
			m_State = P_JUMP;
			m_isGround = false;
		}
	}

	if (jumpSpeed > 1.0f && KEYMANAGER->isStayKeyDown(VK_DOWN) || gravity > 0.1f && KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		m_State = P_DOWNATTACK;
		m_AttackDownRc = RectMake(m_fX + 7, m_fY + 20, 17, 10);
	}

	if (KEYMANAGER->isOnceKeyDown('X')) {
		SOUNDMANAGER->play("플레이어공격", 1.0f);
		m_State = P_ATTACK;
		m_isAttack = true;
	}
	
	if (m_State == P_MOVE) {
		if (m_isMovingMap == true) {
			m_State = P_MOVE;
		}
	}
	/*if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_isRight == true && m_isMovingMap) {
		m_State = P_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_isRight == false && m_isMovingMap) {
		m_State = P_MOVE;
	}*/
	/*if (KEYMANAGER->isStayKeyDown(VK_UP) && m_isMovingMap && m_State == P_LADDERUP) {
		m_State = P_LADDERUP;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_isMovingMap && m_State == P_LADDERUP) {
		m_State = P_LADDERUP;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_isMovingMap && m_State == P_DOWNATTACK) {
		m_State = P_DOWNATTACK;
	}

	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_isMovingMap && m_State == P_DOWNATTACK) {
		m_State = P_DOWNATTACK;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_isMovingMap && m_State == P_JUMP) {
		m_State = P_JUMP;
	}*/
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
				m_AttackRc = RectMake(m_fX + 35, m_fY - 5, 25, 25);
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
				m_AttackRc = RectMake(m_fX - 10, m_fY - 5, 25, 25);
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

	else if (m_isDead) {
		m_State = P_DEAD;
		if (m_isRight == true) {
			m_FrameCount++;
			if (m_FrameCount % 17 == 0) {
				m_DEADCount++;
				m_DeathImg->setFrameX(m_DEADCount);

				if (m_DEADCount >= 8) {
					m_DEADCount = 8;
					MAPMANAGER->setSceenSFX(true);
					m_isDead = false;
					//Hp = 12;
				}
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

	//if (Hp <= 0) m_isDead = true;
}

void Player::FireBallMove()
{
	if (m_EquipFlameWand == true) {
		if (KEYMANAGER->isOnceKeyDown('V')) {
			if (Mana >= 2) {
				Mana -= 2;
				//m_State = KnifeShot;
				if (m_isRight) {
					m_bullet.x = m_fX + 30;
					m_bullet.y = m_fY + 8;
					m_bullet.angle = 0;
					v_Bullet.push_back(m_bullet);
				}
				else if (!m_isRight) {
					m_isFireLeft = true;
					m_bullet.x = m_fX - 4;
					m_bullet.y = m_fY + 8;
					m_bullet.angle = 0;
					v_Bullet.push_back(m_bullet);
				}
			}
		}
	}

	for (v_IterBullet = v_Bullet.begin(); v_IterBullet != v_Bullet.end();) {
		if (m_isFireLeft == false) {
			v_IterBullet->x += cosf(v_IterBullet->angle) * 2.5f;
			v_IterBullet->y -= sinf(v_IterBullet->angle) * 2.5f;
			v_IterBullet->rc = RectMakeCenter(v_IterBullet->x, v_IterBullet->y, 12, 12);

			if (v_IterBullet->x > MAPMANAGER->getCamera().x + 400) {
				v_IterBullet = v_Bullet.erase(v_IterBullet);
			}
			else ++v_IterBullet;
		}
		else if (m_isFireLeft == true) {
			v_IterBullet->x -= cosf(v_IterBullet->angle) * 2.5f;
			v_IterBullet->y -= sinf(v_IterBullet->angle) * 2.5f;
			v_IterBullet->rc = RectMakeCenter(v_IterBullet->x, v_IterBullet->y, 12, 12);

			if (v_IterBullet->x < MAPMANAGER->getCamera().x) {
				v_IterBullet = v_Bullet.erase(v_IterBullet);
				m_isFireLeft = false;
			}
			else ++v_IterBullet;
		}

		
	}
}

void Player::ShovelRender(HDC hdc)
{
	if (m_State == P_IDLE) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_IdleImg->frameAlphaRender(hdc, m_fX, m_fY - 8, 0, 0, m_invincibleAlpha);
			else if (!m_isRight) m_IdleImg->frameAlphaRender(hdc, m_fX - 2, m_fY - 8, 0, 1, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_IdleImg->frameRender(hdc, m_fX, m_fY - 8, 0, 0);
			else if (!m_isRight) m_IdleImg->frameRender(hdc, m_fX - 2, m_fY - 8, 0, 1);
		}
	}
	
	else if (m_State == P_MOVE) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_MoveImg->frameAlphaRender(hdc, m_fX, m_fY - 11, m_CurrFrameX, 0, m_invincibleAlpha);
			else if (!m_isRight) m_MoveImg->frameAlphaRender(hdc, m_fX - 8, m_fY - 11, m_CurrFrameX, 1, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_MoveImg->frameRender(hdc, m_fX, m_fY - 11, m_CurrFrameX, 0);
			else if (!m_isRight) m_MoveImg->frameRender(hdc, m_fX - 8, m_fY - 11, m_CurrFrameX, 1);
		}
	}
	
	else if (m_isAttack) {
		if (m_invincibleTime == true) {
			if (m_isRight) m_AttackImg->frameAlphaRender(hdc, m_fX, m_fY - 9, m_AtkFrameCount, m_CurrFrameY, m_invincibleAlpha);
			else if (!m_isRight) m_AttackImg->frameAlphaRender(hdc, m_fX - 19, m_fY - 9, m_AtkFrameCount, m_CurrFrameY, m_invincibleAlpha);
		}
		else {
			if (m_isRight) m_AttackImg->frameRender(hdc, m_fX, m_fY - 9, m_AtkFrameCount, m_CurrFrameY);
			else if (!m_isRight) m_AttackImg->frameRender(hdc, m_fX - 19, m_fY - 9, m_AtkFrameCount, m_CurrFrameY);
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
		m_AppearImg->frameRender(hdc, m_fX - 22, m_fY - 24, m_CurrFrameX, 0);
	}

	else if (m_State == P_DEAD) {
		if (m_isRight) m_DeathImg->frameRender(hdc, m_fX - 5, m_fY - 7, m_DEADCount, 0);
	}

	for (v_IterBullet = v_Bullet.begin(); v_IterBullet != v_Bullet.end(); v_IterBullet++) {
		Rectangle(hdc, v_IterBullet->rc.left, v_IterBullet->rc.top, v_IterBullet->rc.right, v_IterBullet->rc.bottom);
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
			m_isFalling = false;
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
	if (m_isMovingMap == false) {
		if (IntersectRect(&rc, &m_rc, &x)) {
			gravity = 0;
			jumpSpeed = 0;
			m_isGround = true;
			m_fY += 0;

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

void Player::SpikeColliosion(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_rc, &x)) {
		if (m_isDeadCHeck == false) SOUNDMANAGER->play("으앙주금", 0.8f);
		m_isFalling = false;
		m_fY = x.top - 24;
		gravity = 0;
		jumpSpeed = 0;
		m_isGround = true;
		Hp = 0;
		m_isDead = true;
		m_State = P_DEAD;
		m_isDeadCHeck = true;

	}
}

void Player::SaveColliosion(RECT x)
{
	if (m_isCheck == false) {
		RECT rc;
		if (IntersectRect(&rc, &m_rc, &x)) {
			SOUNDMANAGER->play("세이브체크", 0.7f);
			//MAPMANAGER->setCheckOn(true);
			MAPMANAGER->SavePoint();
			m_isCheck = true;
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
			if (jumpSpeed > 0) {
				m_isGround = false;
			}
		}
	}
}

void Player::DownATKtoOBJCollision(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_AttackDownRc, &x)) {
		if (m_AttackDownRc.bottom > x.top - 20) {
			gravity = 0;
			jumpSpeed = 0;

			if (jumpSpeed <= 0.0f) {
				jumpSpeed += 5.1f;
			}
			else {
				if (jumpSpeed > 0.1f) {
					m_isGround = false;
					gravity += 3.0f;
				}
			}

			
		}
	}
}

void Player::OBJCollision(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_rc, &x)) {

		if (m_rc.right < x.left + 4) {
			m_fX -= 2.0f;
			m_State = P_IDLE;
		}

		else if (m_rc.left > x.right - 4) {
			m_fX += 2.0f;
			m_State = P_IDLE;
		}

		else if (m_rc.bottom > x.bottom) {
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
			m_fY = x.top - 23;
			gravity = 0;
			jumpSpeed = 0;
			m_isGround = true;
		}
	}

	else {
		m_isGround = false;
		m_isFalling = true;
	}
}

void Player::UIrender(HDC hdc)
{
	m_Number_1->frameRender(hdc, MAPMANAGER->getCamera().x + 15, MAPMANAGER->getCamera().y + 9, Money / 1000, 0);
	m_Number_2->frameRender(hdc, MAPMANAGER->getCamera().x + 23, MAPMANAGER->getCamera().y + 9, Money % 1000 % 1000 / 100, 0);
	m_Number_3->frameRender(hdc, MAPMANAGER->getCamera().x + 31, MAPMANAGER->getCamera().y + 9, Money % 1000 % 100 / 10, 0);
	m_Number_4->frameRender(hdc, MAPMANAGER->getCamera().x + 39, MAPMANAGER->getCamera().y + 9, 0, 0);

	if (m_isPlusHp) m_HpBar5->frameRender(hdc, MAPMANAGER->getCamera().x + 193, MAPMANAGER->getCamera().y + 8, Hp - 8, 0);
	m_HpBar4->frameRender(hdc, MAPMANAGER->getCamera().x + 184, MAPMANAGER->getCamera().y + 8, Hp - 6, 0);
	m_HpBar3->frameRender(hdc, MAPMANAGER->getCamera().x + 175, MAPMANAGER->getCamera().y + 8, Hp - 4, 0);
	m_HpBar2->frameRender(hdc, MAPMANAGER->getCamera().x + 166, MAPMANAGER->getCamera().y + 8, Hp - 2, 0);
	m_HpBar1->frameRender(hdc, MAPMANAGER->getCamera().x + 157, MAPMANAGER->getCamera().y + 8, Hp, 0);

	m_HpKAn->render(hdc, MAPMANAGER->getCamera().x + 157, MAPMANAGER->getCamera().y + 8);
	m_HpKAn->render(hdc, MAPMANAGER->getCamera().x + 166, MAPMANAGER->getCamera().y + 8);
	m_HpKAn->render(hdc, MAPMANAGER->getCamera().x + 175, MAPMANAGER->getCamera().y + 8);
	m_HpKAn->render(hdc, MAPMANAGER->getCamera().x + 184, MAPMANAGER->getCamera().y + 8);
	if (m_isPlusHp) m_HpKAn->render(hdc, MAPMANAGER->getCamera().x + 193, MAPMANAGER->getCamera().y + 8);
}

Player::Player() 
{
}


Player::~Player()
{
}

#include "stdafx.h"
#include "Player.h"
#include "Texture.h"
#include "utils.h"

Texture* Player::m_pTex{ nullptr };
int Player::m_InstanceCounter{};


Player::Player()
	:m_Pos{ 10.0f,10.0f }
{
}

Player::Player(float x, float y)
	: m_Pos{ x,y },
	m_WorldRect{m_Pos.x,m_Pos.y,m_TexPartSizeW*2,m_TexPartSizeH*2}
{

	if (m_InstanceCounter == 0)
	{
		m_pTex = new Texture{ "./DAE_Sprites/DAE_Sprites_Knight.png" };
	}
	m_InstanceCounter++;
}


Player::~Player()
{
	m_InstanceCounter--;
	if (m_InstanceCounter == 0)
	{
		delete m_pTex;
		m_pTex = nullptr;
}
}

void Player::Draw()
{
	m_WorldRect = Rectf{m_Pos.x,m_Pos.y,m_WorldRect.width,m_WorldRect.height};
	if (m_pTex->IsCreationOk())
	{
		if (m_AttackState)
		{
			CheckAttackFrame();
		}
		else if (m_JumpState)
		{
			CheckJumpFrame();
		}
		else if (m_RunState != Direction::Stationary)
		{
			CheckRunFrame();
		}
		else if (m_RunState == Direction::Stationary)
		{
			m_Frame.bottom = 0.0f;
			m_Frame.left = 0.0f;
			m_RunFrameNr = 0;
		}
		m_pTex->Draw(m_WorldRect, m_Frame);
	}
	else
	{
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(m_Pos.x, m_Pos.y);
	glVertex2f(m_Pos.x + m_TexPartSizeW, m_Pos.y);
	glVertex2f(m_Pos.x + m_TexPartSizeW, m_Pos.y + m_TexPartSizeH);
	glVertex2f(m_Pos.x, m_Pos.y + m_TexPartSizeH);

	glEnd();
}

}

void Player::Update(float elapsedSec, float gravity, Rectf ground)
{
	m_PrevPos = m_Pos;
	switch (m_RunState)
	{
	case Direction::Stationary:
		break;
	case Direction::Left:
		m_Velocity = -m_Acceleration;
		break;
	case Direction::Right:
		m_Velocity = m_Acceleration;
		break;
	}

	if (m_AttackState)
	{
		if (m_AttackFrameNr == 0)
		{
			m_AttackFrameNr++;
		}
		m_aFrameCounter++;
		if (m_aFrameCounter > 5)
		{
			m_AttackFrameNr++;
			if (m_AttackFrameNr > 3)
			{
				m_AttackFrameNr = 0;
				m_AttackState = false;
			}
			m_aFrameCounter = 0;
		}

	}
	if (m_JumpState)
	{
		m_JumpVelocity += gravity*elapsedSec;
		m_Pos.y += m_JumpVelocity;
		if (!m_AttackState)
		{
			if (m_JumpVelocity > 0)
			{
				m_JumpFrameNr = 1;
			}
			else
			{
				m_JumpFrameNr = 2;
			}
		}

		if (m_Pos.y < ground.bottom+ground.height)
		{
			m_Pos.y = ground.bottom+ground.height;
			m_JumpFrameNr = 3;
			m_JumpState = false;
			m_JumpVelocity = m_JumpAcceleration;
		}
		
	}

	if (m_RunState != Direction::Stationary)
	{
		if (m_JumpState)
		{
			m_RunFrameNr = 0;
		}
		else
		{
			m_rFrameCounter++;
			if (m_rFrameCounter > 5)
			{
				m_RunFrameNr++;
				if (m_RunFrameNr > 8)
				{
					m_RunFrameNr = 1;
				}
				m_rFrameCounter = 0;
			}

		}

		m_Pos.x += m_Velocity*elapsedSec;
	}
}

void Player::CheckColl(Rectf obj)
{
	bool IsCollided{ dae::IsPointInRect(m_Pos,obj)};
	if (IsCollided)
	{
		m_Pos = m_PrevPos;
	}
}

bool Player::GetJumpState()
{
	return m_JumpState;
}

Direction Player::GetRunState()
{
	return m_RunState;
}

bool Player::GetAttackState()
{
	return m_AttackState;
}

Point2f Player::GetPos()
{
	return m_Pos;
}

void Player::SetJumpState(bool newJS)
{
	m_JumpState = newJS;
}

void Player::SetRunState(Direction newRS)
{
	m_RunState = newRS;
}

void Player::SetAttackState(bool newAS)
{
	m_AttackState = newAS;
}

void Player::CheckJumpFrame()
	{
	switch (m_JumpFrameNr)
		{
	case 0:
		m_Frame.bottom = 0.0f;
		m_Frame.left = 0.0f;
		break;

	case 1:
		m_Frame.bottom = 0.0f;
		m_Frame.left = m_TexPartSizeW;
		break;

	case 2:
		m_Frame.bottom = 0.0f;
		m_Frame.left = m_TexPartSizeW * 2;
		break;

	case 3:
		m_Frame.bottom = 0.0f;
		m_Frame.left = m_TexPartSizeW * 3;
		break;

	default:
		break;
		}
	}

void Player::CheckRunFrame()
{
	switch (m_RunFrameNr)
	{
	case 0:
		m_Frame.bottom = 0.0f;
		m_Frame.left = 0.0f;
		break;

	case 1:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = 0.0f;
		break;

	case 2:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW;
		break;

	case 3:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 2;
		break;

	case 4:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 3;
		break;

	case 5:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 4;
		break;

	case 6:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 5;
		break;

	case 7:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 6;
		break;

	case 8:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 7;
		break;
}
}

void Player::CheckAttackFrame()
{
	switch (m_AttackFrameNr)
	{
	case 0:
		m_Frame.bottom = 0.0f;
		m_Frame.left = 0.0f;
		break;

	case 1:
		m_Frame.bottom = m_TexPartSizeH * 2;
		m_Frame.left = m_TexPartSizeW * 5;
		break;

	case 2:
		m_Frame.bottom = m_TexPartSizeH * 2;
		m_Frame.left = m_TexPartSizeW * 6;
		break;

	case 3:
		m_Frame.bottom = m_TexPartSizeH * 2;
		m_Frame.left = (m_TexPartSizeW * 7);
		break;
	}

}

void Player::SetJumpVelocity(float NewJumpVel)
{
	m_JumpVelocity = NewJumpVel;
}

void Player::SetVelocity(float NewVel)
{
	m_Velocity = NewVel;
}

float Player::GetJumpVelocity()
{
	return m_JumpVelocity;
}

float Player::GetVelocity()
{
	return m_Velocity;
}

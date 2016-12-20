#include "stdafx.h"
#include "Player.h"
#include "Texture.h"

Texture* Player::m_pTex{ nullptr };
int Player::m_InstanceCounter{};


Player::Player()
	:m_Pos{10.0f,10.0f}
{
}

Player::Player(float x, float y)
	:m_Pos{x,y},
	 m_Frame{0.0f,0.0f,25.0f,25.0f}
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
		else if(m_RunState == Direction::Stationary)
		{
			m_Frame.bottom = 0.0f,
			m_Frame.left = 0.0f;
			m_RunFrameNr = 0;
		}
		m_pTex->Draw(Rectf{m_Pos.x,m_Pos.y,m_TexPartSizeW *2,m_TexPartSizeH*2}, m_Frame);
	}
	else
	{
		glBegin(GL_QUADS);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex2f(m_Pos.x, m_Pos.y);
		glVertex2f(m_Pos.x+m_TexPartSizeW, m_Pos.y);
		glVertex2f(m_Pos.x+ m_TexPartSizeW, m_Pos.y+ m_TexPartSizeH);
		glVertex2f(m_Pos.x, m_Pos.y+ m_TexPartSizeH);

		glEnd();
	}
	
}

void Player::Update(float elapsedSec, float totalElapsedSec, float ground)
{
	float speed{};
	switch (m_RunState)
	{
	case Direction::Stationary:
		break;
	case Direction::Left:
		speed = -m_Speed;
		break;
	case Direction::Right:
		speed = m_Speed;
		break;
	}

	if (m_AttackState)
	{
		m_aFrameCounter++;
		if (m_aFrameCounter > 240)
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
		if (m_AttackState)
		{
			m_Pos.y += (m_JumpVelocity - (5.0f*totalElapsedSec));
		}
		else
		{
			m_Pos.y += (m_JumpVelocity - (5.0f*totalElapsedSec));
			if (m_JumpVelocity - (5.0f*totalElapsedSec) > 0)
			{
				m_JumpFrameNr = 1;
			}
			else
			{
				m_JumpFrameNr = 2;
			}
	
			if (m_Pos.y <= ground)
			{
				m_Pos.y = ground;
				m_JumpFrameNr = 3;
				m_JumpState = false;
			}
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
			if (m_rFrameCounter > 500)
			{
				m_RunFrameNr++;
				if (m_RunFrameNr > 8)
				{
					m_RunFrameNr = 1;
				}
				m_rFrameCounter = 0;
			}
			
		}
		
		m_Pos.x += speed*elapsedSec;
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
		m_Frame.bottom =0.0f;
		m_Frame.left = m_TexPartSizeW;
		break;

	case 2:
		m_Frame.bottom = 0.0f;
		m_Frame.left = m_TexPartSizeW*2;
		break;

	case 3:
		m_Frame.bottom =0.0f;
		m_Frame.left = m_TexPartSizeW*3;
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

	case 3:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 2;

	case 4:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 3;

	case 5:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 4;

	case 6:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 5;

	case 7:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 6;

	case 8:
		m_Frame.bottom = m_TexPartSizeH;
		m_Frame.left = m_TexPartSizeW * 7;
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
		m_Frame.bottom = m_TexPartSizeH*2;
		m_Frame.left = m_TexPartSizeW * 4;
		break;

	case 2:
		m_Frame.bottom = m_TexPartSizeH * 2;
		m_Frame.left = m_TexPartSizeW * 5;
		break;

	case 3:
		m_Frame.bottom = m_TexPartSizeH * 2;
		m_Frame.left = (m_TexPartSizeW * 6);
		break;
	}
}


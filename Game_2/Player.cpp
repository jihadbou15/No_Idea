#include "stdafx.h"
#include "Player.h"


Player::Player()
	:m_Pos{10.0f,10.0f}
{
}

Player::Player(float x, float y)
	:m_Pos{x,y}
{

}


Player::~Player()
{
}

void Player::Draw()
{
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(m_Pos.x, m_Pos.y);
	glVertex2f(m_Pos.x+20, m_Pos.y);
	glVertex2f(m_Pos.x+20, m_Pos.y+20);
	glVertex2f(m_Pos.x, m_Pos.y+20);

	glEnd();
}

void Player::Update(float elapsedSec, bool jumpState, float Camera)
{
	if (jumpState = true)
	{
		m_Pos.y += (m_JumpVelocity - (5.0f*elapsedSec));
		if (m_Pos.y <= 10.0f)
		{
			m_Pos.y = 10.0f;

		}
	}

}

Point2f Player::GivePlayerPos()
{
	return(m_Pos);
}

void Player::Move(bool leftState, bool rightState, bool borderRight)
{
	if (borderRight == false)
	{
		if (leftState == true)
		{
			++m_Pos.x;
		}
		else
			if (rightState == true)
			{
				--m_Pos.x;
			}
	}
}
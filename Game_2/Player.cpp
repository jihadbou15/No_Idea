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
	 m_Frame{0.0f,0.0f,m_TexPartSize,m_TexPartSize}
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
		m_pTex->Draw(Rectf{m_Pos.x,m_Pos.y,m_TexPartSize,m_TexPartSize}, m_Frame);
	}
	else
	{
		glBegin(GL_QUADS);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex2f(m_Pos.x, m_Pos.y);
		glVertex2f(m_Pos.x+m_TexPartSize, m_Pos.y);
		glVertex2f(m_Pos.x+ m_TexPartSize, m_Pos.y+ m_TexPartSize);
		glVertex2f(m_Pos.x, m_Pos.y+ m_TexPartSize);

		glEnd();
	}
	
}

void Player::Update(float elapsedSec, bool jumpState)
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


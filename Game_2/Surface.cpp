#include "stdafx.h"
#include "Surface.h"



Surface::Surface()
{
}

Surface::Surface(float x, float y)
:m_Pos{x,y}
{

}

Surface::~Surface()
{
}

void Surface::Draw()
{
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(m_Pos.x, m_Pos.y);
	glVertex2f(m_Pos.x, m_Pos.y + 50.0f);
	glVertex2f(m_Pos.x + 50.0f, m_Pos.y + 50.0f);
	glVertex2f(m_Pos.x + 50.0f, m_Pos.y);
	glEnd();
}

void Surface::Update(Point2f camera, Direction player1)
{
	if (player1 == Direction::Right)
	{
		m_Pos.x -= camera.x;
	}
	
}
#include "stdafx.h"
#include "Element.h"
#include "Texture.h"

Texture* Element::m_pTex{ nullptr };
int Element::m_InstanceCounter{};
float Element::m_TextPartSize{ 16.0f };



Element::Element(Rectf texPart, Rectf rectWorld) : m_TexPart{texPart}, m_RectWorld{rectWorld}, m_IsDisplayed{true}
{
	
	if (m_InstanceCounter == 0)
	{
		m_pTex = new Texture{ "./DAE_Sprites/EnvironmentGrid.png" };
	}
	m_InstanceCounter++;
}

Element::Element(Point2f pos, Rectf rectWorld) : 
	Element( Rectf{ pos.x, pos.y, m_TextPartSize, m_TextPartSize }, rectWorld)
{
}

Element::Element(Rectf texPart) :
	Element(texPart,Rectf{0.0f,0.0f,texPart.width,texPart.height})
{
}


void Element::Draw()
{
	if (m_IsDisplayed)
	{
		m_pTex->Draw( m_RectWorld,m_TexPart);
	}
	
}

void Element::Draw(Point2f pos)
{
	SetRectWorld(pos);
	if (m_IsDisplayed)
	{
		m_pTex->Draw(m_RectWorld, m_TexPart);
	}
}

void Element::SetTextPart(Rectf textPart)
{
	m_TexPart = textPart;
}

void Element::SetRectWorld(Rectf rectWorld)
{
	m_RectWorld = rectWorld;
}

void Element::SetRectWorld(Point2f pos)
{
	Rectf newRect{ pos.x,pos.y,m_RectWorld.width,m_RectWorld.height };
	m_RectWorld = newRect;
}

void Element::SetDisplay(bool isDisplayed)
{
	m_IsDisplayed = isDisplayed;
}

Point2f Element::GetPos()
{
	return Point2f(m_RectWorld.left,m_RectWorld.bottom);
}

float Element::GetWidth()
{
	return m_RectWorld.width;
}

float Element::GetHeight()
{
	return m_RectWorld.height;
}


float Element::GetSize()
{
	return m_TextPartSize;
}

Element::~Element()
{
	m_InstanceCounter--;
	if (m_InstanceCounter == 0)
	{
		delete m_pTex;
		m_pTex = nullptr;
	}
}

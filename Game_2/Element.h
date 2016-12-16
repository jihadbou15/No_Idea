#pragma once
#include "Texture.h"

class Element
{
public:
	static Texture m_Tex;
	
	Element();
	
	void Draw();
	
	~Element();

private:
	Rectf m_TexPart;
	Rectf m_RectWorld;

};


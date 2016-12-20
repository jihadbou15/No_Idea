#pragma once

class Texture;

class Element
{
public:
	Element(Rectf texPart, Rectf rectWorld);
	Element(Point2f pos, Rectf rectWorld);
	
	void Draw();
	void SetTextPart(Rectf textPart);
	void SetRectWorld(Rectf rectWorld);
	void SetDisplay(bool isDisplayed);
	Point2f GetPos();
	float GetWidth();
	float GetHeight();
	static float GetSize();

	~Element();

private:
	
	static float m_TextPartSize;

	Rectf m_TexPart;
	Rectf m_RectWorld;
	bool m_IsDisplayed;
	static Texture* m_pTex;
	static int m_InstanceCounter;
};


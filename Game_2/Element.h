#pragma once

class Texture;

class Element
{
public:
	Element(Rectf texPart, Rectf rectWorld);
	Element(Point2f pos, Rectf rectWorld);
	Element(Rectf texPart);
	
	void Draw();
	void Draw(Point2f pos);
	void SetTextPart(Rectf textPart);
	void SetRectWorld(Rectf rectWorld);
	void SetRectWorld(Point2f pos);
	void SetDisplay(bool isDisplayed);
	Point2f GetPos();
	float GetWidth();
	float GetHeight();
	static float GetSize();

	~Element();

private:
	
	static float m_TextPartSize;
	static Texture* m_pTex;
	static int m_InstanceCounter;

	Rectf m_TexPart;
	Rectf m_RectWorld;
	bool m_IsDisplayed;
	
};


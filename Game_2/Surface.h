#pragma once
#include "Player.h"
class Surface
{
public:
	Surface();
	Surface(float x, float y);
	~Surface();
	void Draw(  );
	void Update(Point2f camera, Direction player);
private:
	Point2f m_Pos;
};


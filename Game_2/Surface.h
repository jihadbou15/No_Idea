#pragma once
class Surface
{
public:
	Surface();
	Surface(float x, float y);
	~Surface();
	void Draw(  );
	void Update(Point2f camera);
private:
	Point2f m_Pos;
};


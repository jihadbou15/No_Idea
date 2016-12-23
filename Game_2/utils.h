#pragma once

namespace dae
{
	void SetColor( const Color4f& color );
	
	void DrawPoint( float x, float y, float pointSize = 1.0f );
	void DrawPoint( const Point2f & p, float pointSize = 1.0f );
	void DrawPoints( Point2f *pVertices, int nrVertices, float pointSize = 1.0f );

	void DrawLine( float x1, float y1, float x2, float y2, float lineWidth = 1.0f );
	void DrawLine( const Point2f & p1, const Point2f & p2, float lineWidth = 1.0f );

	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Point2f & bottomLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Rectf & rect, float lineWidth = 1.0f);
	void FillRect(float left, float bottom, float width, float height);
	void FillRect(const Point2f & bottomLeft, float width, float height);
	void FillRect(const Rectf & rect);

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Point2f & center, float radX, float radY, float lineWidth = 1.0f);
	void FillEllipse(float centerX, float centerY, float radX, float radY);
	void FillEllipse(const Point2f & center, float radX, float radY);

	void DrawArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f );
	void DrawArc( const Point2f & center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f );
	void FillArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle );
	void FillArc( const Point2f & center, float radX, float radY, float fromAngle, float tillAngle );

	void DrawPolygon( Point2f *pVertices, int nrVertices, bool closed = true, float lineWidth = 1.0f );
	void FillPolygon( Point2f *pVertices, int nrVertices);


	int GetIndex(int iRow, int iColumn, int columns);
	bool isOverLapping(const Rectf &shape1, const Rectf &shape2);
	bool IsPointInRect(const Point2f &point, const Rectf &rect);
	void DrawFilledRect(const Rectf &rectangle, const Color4f &color);
}
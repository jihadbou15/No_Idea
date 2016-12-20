#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "utils.h"

namespace dae
{
	void SetColor( const Color4f& color )
	{
		glColor4f( color.r, color.g, color.b, color.a );
	}

	void DrawPoint( float x, float y, float pointSize )
	{
		glPointSize( pointSize );
		glBegin( GL_POINTS );
		{
			glVertex2f( x, y );
		}
		glEnd( );
	}

	void DrawPoint( const Point2f & p, float pointSize )
	{
		DrawPoint( p.x, p.y, pointSize );
	}

	void DrawPoints( Point2f *pVertices, int nrVertices, float pointSize )
	{
		glPointSize( pointSize );
		glBegin( GL_POINTS );
		{
			for ( int idx{ 0 }; idx < nrVertices; ++idx )
			{
				glVertex2f( pVertices[idx].x, pVertices[idx].y );
			}
		}
		glEnd( );
	}

	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		{
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		}
		glEnd();
	}

	void DrawLine( const Point2f & p1, const Point2f & p2, float lineWidth )
	{
		DrawLine( p1.x, p1.y, p2.x, p2.y, lineWidth );
	}

	void DrawRect(float left, float bottom, float width, float height, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f( left, bottom );
			glVertex2f( left + width, bottom );
			glVertex2f( left + width, bottom + height );
			glVertex2f( left, bottom + height );
		}
		glEnd();
	}

	void DrawRect(const Point2f & bottomLeft, float width, float height, float lineWidth)
	{
		DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
	}

	void DrawRect(const Rectf & rect, float lineWidth)
	{
		DrawRect(rect.left, rect.bottom, rect.width, rect.height, lineWidth);
	}

	void FillRect(float left, float bottom, float width, float height)
	{
		glBegin(GL_POLYGON);
		{
			glVertex2f(left, bottom);
			glVertex2f( left + width, bottom );
			glVertex2f(left + width, bottom + height);
			glVertex2f( left, bottom + height );
		}
		glEnd();
	}

	void FillRect(const Point2f & bottomLeft, float width, float height)
	{
		FillRect(bottomLeft.x, bottomLeft.y, width, height);
	}

	void FillRect(const Rectf & rect)
	{
		FillRect(rect.left, rect.bottom, rect.width, rect.height);
	}

	void DrawEllipse( float centerX, float centerY, float radX, float radY, float lineWidth )
	{
		float dAngle{ radX > radY ? float( M_PI / radX ) : float( M_PI / radY ) };

		glLineWidth( lineWidth );
		glBegin( GL_LINE_LOOP );
		{
			for ( float angle = 0.0; angle < float( 2 * M_PI + dAngle ); angle += dAngle )
			{
				glVertex2f( centerX + radX * float( cos( angle ) ), centerY + radY * float( sin( angle ) ) );
			}
		}
		glEnd( );
	}

	void DrawEllipse( const Point2f & center, float radX, float radY, float lineWidth )
	{
		DrawEllipse( center.x, center.y, radX, radY, lineWidth );
	}

	void FillEllipse(float centerX, float centerY, float radX, float radY)
	{
		float dAngle{ radX > radY ? float( M_PI / radX ): float( M_PI / radY ) };

		glBegin( GL_POLYGON );
		{
			for ( float angle = 0.0; angle < float( 2 * M_PI + dAngle ); angle += dAngle )
			{
				glVertex2f( centerX + radX * float( cos( angle ) ), centerY + radY * float( sin( angle ) ) );
			}
		}
		glEnd();
	}

	void FillEllipse(const Point2f & center, float radX, float radY)
	{
		FillEllipse(center.x, center.y, radX, radY);
	}

	void DrawArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth )
	{
		if ( fromAngle > tillAngle )
		{
			return;
		}

		float dAngle{ radX > radY ? float( M_PI / radX ) : float( M_PI / radY ) };

		glLineWidth( lineWidth );
		glBegin( GL_LINE_STRIP );
		{
			for ( float angle = fromAngle; angle < tillAngle; angle += dAngle )
			{
				glVertex2f( centerX + radX * float( cos( angle ) ), centerY + radY * float( sin( angle ) ) );
			}
			glVertex2f( centerX + radX * float( cos( tillAngle ) ), centerY + radY * float( sin( tillAngle ) ) );
		}
		glEnd( );

	}
	
	void DrawArc( const Point2f & center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth )
	{
		DrawArc( center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth );
	}

	void FillArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle )
	{
		if ( fromAngle > tillAngle )
		{
			return;
		}
		float dAngle{ radX > radY ? float( M_PI / radX ) : float( M_PI / radY ) };

		glBegin( GL_POLYGON );
		{
			glVertex2f( centerX, centerY );
			for ( float angle = fromAngle; angle < tillAngle; angle += dAngle )
			{
				glVertex2f( centerX + radX * float( cos( angle ) ), centerY + radY * float( sin( angle ) ) );
			}
			glVertex2f( centerX + radX * float( cos( tillAngle ) ), centerY + radY * float( sin( tillAngle ) ) );
		}
		glEnd( );
	}

	void FillArc( const Point2f & center, float radX, float radY, float fromAngle, float tillAngle )
	{
		FillArc( center.x, center.y, radX, radY, fromAngle, tillAngle );
	}

	void DrawPolygon( Point2f *pVertices, int nrVertices, bool closed, float lineWidth  )
	{
		glLineWidth( lineWidth );
		closed ? glBegin( GL_LINE_LOOP ) : glBegin( GL_LINE_STRIP );
		{
			for ( int idx{ 0 }; idx < nrVertices; ++idx )
			{
				glVertex2f( pVertices[idx].x, pVertices[idx].y );
			}
		}
		glEnd( );
	}

	void FillPolygon( Point2f *pVertices, int nrVertices )
	{
		glBegin( GL_POLYGON );
		{
			for ( int idx{ 0 }; idx < nrVertices; ++idx )
			{
				glVertex2f( pVertices[idx].x, pVertices[idx].y );
			}
		}
		glEnd( );
	}

	int GetIndex(int iRow, int iColumn, int columns)
	{
		int index{ (iRow * columns) + iColumn };

		return index;
	}

}
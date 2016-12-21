#pragma once
#include <iostream>
#include "Player.h"
#include "Element.h"



#include "Surface.h"
class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( );

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

	
	

private:
	// DATA MEMBERS
	Window m_Window;

	//Player
	Player m_Player1;
	float m_TotalElapsedSec;

	//Level
	static const int m_NrElements{ 100 };
	Element* m_pLevelFloor[m_NrElements];
	
	

	//
	bool m_BorderRight{ false };
	Point2f m_CameraPos;
	
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( );
};
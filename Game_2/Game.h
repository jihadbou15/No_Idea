#pragma once
#include <iostream>
#include "Player.h"
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

	bool m_JumpState{ false };

	float m_TotalElapsedSec;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( );
};
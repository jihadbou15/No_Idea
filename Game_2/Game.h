#pragma once
#include <iostream>
#include "Player.h"
#include "Element.h"
#include "Texture.h"

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
	static const int m_NrElementsFloor{ 100 };
	static const int m_NrElementsGrass{25};
	static const int m_NrTrees{ 12 };

	Element* m_pLevelFloor[m_NrElementsFloor];
	Element* m_pLevelGrass[m_NrElementsGrass];
	Element* m_pLevelTreeA;
	Element* m_pLevelTreeB;
	Element* m_pLevelTreeC;

	Point2f m_posTree[m_NrTrees]{};
	const float m_Gravity{ -5.0f };
	
	//Level Hitbox
	Rectf m_Floor;
	Rectf m_Platform1;
	Rectf m_Platform2;
	Rectf m_Platform3;

	//Background
	Texture* m_Background;
	
	// FUNCTIONS
	void Initialize( );
	void InitializeFloor();
	void InitializeGrass();
	void InitializeTrees();
	void Cleanup( );
	void ClearBackground( );
};
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
	void UpdateLasers(float elapsedSec);
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
	bool m_lost{false};
	bool m_info{ true };
	//Player
	Player m_Player1;
	float m_TotalElapsedSec;

	//Level
	static const int m_NrElementsFloor{ 100 };
	static const int m_NrElementsGrass{25};
	static const int m_NrTrees{ 27 };
	static const int m_NrHL{ 3 };
	static const int m_NrVL{ 7 };
	static const int m_NrGL{ 3 };
	Element* m_pLevelFloor[m_NrElementsFloor];
	Element* m_pLevelGrass[m_NrElementsGrass];

	Element* m_pLevelTreeA;
	Element* m_pLevelTreeB;
	Element* m_pLevelTreeC;
	
	Point2f m_posTree[m_NrTrees]{};
	const float m_Gravity{ -10.0f };

	//Lasers
	Rectf m_HorizontalLasers[m_NrHL];
	Rectf m_VerticalLasers[m_NrVL];
	Rectf m_GroundLasers[m_NrGL];
	float m_LaserVelH{600.0f};
	float m_LaserVelV{500.0f};
	float m_LaserVelG{ -600.0f };

	//Level Hitbox
	Rectf m_Floor;

	//Background
	Texture* m_Background;
	
	// FUNCTIONS
	void Initialize( );
	void InitializeFloor();
	void InitializeGrass();
	void InitializeTrees();
	void InitializeLasers();
	void IntializeInfo();
	void InitializeLost();
	void Cleanup( );
	void ClearBackground( );
};
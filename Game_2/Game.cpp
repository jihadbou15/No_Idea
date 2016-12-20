#include "stdafx.h"
#include "Game.h"

#include "utils.h"

Surface Surface1{700.0f,50.0f};



Game::Game(const Window& window)
	:m_Window{ window },
	m_Player1{ 50.0f,(32.0f*2.0f) }
{
	Initialize();
	;
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	Rectf floorTexBase{ Element::GetSize()*2.0f,Element::GetSize() * 2,Element::GetSize(),Element::GetSize()};
	Rectf floorWorld{ 0.0f,0.0f,Element::GetSize() * 2.0f,Element::GetSize() * 2.0f };
	int rows{ 2 };
	int columns{ 50 };
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			m_pLevelFloor[dae::GetIndex(i, j, columns)] = new Element{ floorTexBase,floorWorld };
			floorWorld.left += floorWorld.width;
}
		floorWorld.left = 0.0f;
		floorWorld.bottom += floorWorld.height;
		floorTexBase.bottom -= floorTexBase.height;
	}
}

void Game::Cleanup( )
{
	for (int i = 0; i < m_NrElements; i++)
	{
		delete m_pLevelFloor[i];
		m_pLevelFloor[i] = nullptr;
}
}

void Game::Update( float elapsedSec )
{
	m_TotalElapsedSec += elapsedSec;
	
	if (m_Player1.GetJumpState())
	{
		m_TotalElapsedSec += elapsedSec;
		m_Player1.Update(elapsedSec,m_TotalElapsedSec, float{ (m_pLevelFloor[50]->GetPos().y) + m_pLevelFloor[50]->GetHeight()});
	}
	else
	{

		m_TotalElapsedSec = 0;
		m_Player1.Update(elapsedSec,m_TotalElapsedSec, float{ (m_pLevelFloor[50]->GetPos().y) + m_pLevelFloor[50]->GetHeight() });
	}


	Player1.Move(m_LeftState, m_RightState,m_BorderRight);
	PlayerPos=Player1.GivePlayerPos();
	if (PlayerPos.x >= (m_Window.width / 2 + 20))
	{
		++m_CameraPos.x;
		m_BorderRight = true;
		PlayerPos.x = (m_Window.width / 2 + 20);
		
}
	else
	{
		m_BorderRight = false;
	}
	Surface1.Update(m_CameraPos);
}

void Game::Draw( )
{
	ClearBackground( );
	m_Player1.Draw();
	Surface1.Draw();
	for (int i = 0; i < m_NrElements; i++)
	{
		m_pLevelFloor[i]->Draw();
	
}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		//std::cout << "Jump" << std::endl;
		if (!m_Player1.GetJumpState())
		{
			m_Player1.SetJumpState(true);
		}
		break;
	case SDLK_LEFT:
		//std::cout << "Left" << std::endl;
		m_Player1.SetRunState(Direction::Left);
		break;
	case SDLK_RIGHT:
		//std::cout << "Right" << std::endl;
		m_Player1.SetRunState(Direction::Right);
		break;
	case SDLK_z:
		//std::cout << "Attack" << std::endl;
		m_Player1.SetAttackState(true);
		break;
	}
		
}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		m_Player1.SetRunState(Direction::Stationary);
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		m_Player1.SetRunState(Direction::Stationary);
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );


}

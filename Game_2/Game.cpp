#include "stdafx.h"
#include "Game.h"

#include "utils.h"



Game::Game(const Window& window)
	:m_Window{ window }
	,m_Player1{ 50.0f,(32.0f*2.0f) }
{
	Initialize();
	
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

	if (m_JumpState == true)
	{
		m_TotalElapsedSec += elapsedSec;
		m_Player1.Update(m_TotalElapsedSec, m_JumpState);
	}
	else
	{
		m_TotalElapsedSec = 0;
	}
}

void Game::Draw( )
{
	ClearBackground( );
	m_Player1.Draw();

	for (int i = 0; i < m_NrElements; i++)
	{
		m_pLevelFloor[i]->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:
		std::cout << "Jump" << std::endl;
		if (m_JumpState==false)
		{
			m_JumpState = true;
		}
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
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

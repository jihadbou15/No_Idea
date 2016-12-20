#include "stdafx.h"
#include "Game.h"

Player Player1{ 50.0f,50.0f };
Surface Surface1{700.0f,50.0f};

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{

}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_TotalElapsedSec += elapsedSec;

	Point2f PlayerPos{  };

	if (m_JumpState == true)
	{
		
		Player1.Update(m_TotalElapsedSec, m_JumpState, m_CameraPos.x);
		PlayerPos = Player1.GivePlayerPos();
		if (PlayerPos.y <= 10)
		{
			m_JumpState = false;
		}

	}
	else
	{

		m_TotalElapsedSec = 0;
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

	Player1.Draw();
	Surface1.Draw();
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
	case SDLK_d:
		std::cout << "Left" << std::endl;
		if (m_LeftState == false)
		{
			m_LeftState = true;
		}
		break;
	case SDLK_a:
		if (m_RightState == false)
		{
			m_RightState = true;
		}
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_d:
		if (m_LeftState == true)
		{
			m_LeftState = false;
		}
	break;
	case SDLK_a:
		if (m_RightState == true)
		{
			m_RightState = false;
		}
		break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
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

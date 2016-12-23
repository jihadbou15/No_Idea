#include "stdafx.h"
#include "Game.h"
#include "utils.h"




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
	m_Background = new Texture{ "./DAE_Sprites/background.png" };
	InitializeFloor();
	InitializeGrass();
	InitializeTrees();
	InitializeLasers();
}

void Game::InitializeFloor()
{
	Rectf floorTexBase{ Element::GetSize()*2.0f,Element::GetSize() * 2,Element::GetSize(),Element::GetSize() };
	Rectf floorWorld{ 0.0f,0.0f,Element::GetSize()*2,Element::GetSize()*2 };
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

	m_Floor = Rectf{ 0.0f,0.0f,Element::GetSize() * 4,Element::GetSize() * 4 };

}

void Game::InitializeGrass()
{
	Rectf floorTexBase{ 0.0f,0.0f,Element::GetSize()*14,Element::GetSize() };
	Rectf floorWorld{ 0.0f,Element::GetSize() * 4 ,Element::GetSize() *14,Element::GetSize() };
	for (int i = 0; i < m_NrElementsGrass; i++)
	{
		m_pLevelGrass[i] = new Element{ floorTexBase,floorWorld };
		floorWorld.left += floorWorld.width;
	}
}

void Game::InitializeTrees()
{
	Rectf Tree_A{ Element::GetSize() * 5,Element::GetSize() * 5,Element::GetSize() * 2,Element::GetSize() * 3 };
	Rectf Tree_B{ Element::GetSize() * 7,Element::GetSize() * 4,Element::GetSize() * 3,Element::GetSize() * 4 };
	Rectf Tree_C{ Element::GetSize() * 10,Element::GetSize() * 4,Element::GetSize() * 2,Element::GetSize() * 4 };

	m_pLevelTreeA = new Element{ Tree_A };
	m_pLevelTreeB = new Element{ Tree_B };
	m_pLevelTreeC = new Element{ Tree_C };

	
	for (int i = 0; i < m_NrTrees; i++)
	{
		m_posTree[i].y = 64.0f;
		m_posTree[i].x = 50.0f*i;
	}
}

void Game::InitializeLasers()
{
	Point2f size{ 200.0f,100.0f };
	for (int i = 0; i < m_NrHL; i++)
	{
		m_HorizontalLasers[i] = Rectf{ 0.0f - size.x,m_Window.height - (300.0f * i), size.x,size.y };
	}

	for (int i = 0; i < m_NrVL; i++)
	{
		m_VerticalLasers[i] = Rectf{ m_Window.width - (300.0f * i),0.0f, size.y,size.x };
	}

	for (int i = 0; i < m_NrGL; i++)
	{
		m_GroundLasers[i] = Rectf{ m_Window.width - (400.0f * i),64.0f,size.x,size.y };
	}
}

void Game::Cleanup( )
{
	for (int i = 0; i < m_NrElementsFloor; i++)
	{
		delete m_pLevelFloor[i];
		m_pLevelFloor[i] = nullptr;
	}
	for (int i = 0; i <m_NrElementsGrass; i++)
	{
		delete m_pLevelGrass[i];
		m_pLevelGrass[i] = nullptr;
	}
	
	delete m_Background;
	delete m_pLevelTreeA;
	delete m_pLevelTreeB;
	delete m_pLevelTreeC;

	m_pLevelTreeA = nullptr;
	m_pLevelTreeB = nullptr;
	m_pLevelTreeC = nullptr;
	m_Background = nullptr;

}

void Game::Update(float elapsedSec)
{
	if (!m_info)
	{
		if (!m_lost)
		{
			if (m_Player1.GetJumpState())
			{
				m_TotalElapsedSec += elapsedSec;
			}
			else
			{
				m_TotalElapsedSec = 0;
			}
			m_Player1.Update(elapsedSec, m_Gravity, m_Floor);
			UpdateLasers(elapsedSec);
		}
	}
	
	
}

void Game::UpdateLasers(float elapsedSec)
{
	for (int i = 0; i < m_NrHL; i++)
	{
		m_HorizontalLasers[i].left += m_LaserVelH*elapsedSec;
		if (m_HorizontalLasers[i].left > m_Window.width)
		{
			m_HorizontalLasers[i].left = -m_HorizontalLasers[i].width;
		}
	}

	for (int i = 0; i < m_NrVL; i++)
	{
		m_VerticalLasers[i].bottom -= m_LaserVelV*elapsedSec;
		if (m_VerticalLasers[i].bottom+ m_VerticalLasers[i].height < 0.0f)
		{
			m_VerticalLasers[i].bottom = m_Window.height;
		}
	}

	for (int i = 0; i < m_NrGL; i++)
	{
		m_GroundLasers[i].left += m_LaserVelG*elapsedSec;
		if (m_GroundLasers[i].left + m_GroundLasers[i].width < 0.0f)
		{
			m_GroundLasers[i].left = m_Window.width;
		}
	}
}

void Game::Draw()
{
	
	ClearBackground();
	if (m_lost)
	{

	}
	else if (m_info)
	{

	}
	else
	{
		m_Background->Draw(Rectf{ 0.0f,0.0f,m_Window.width,m_Window.height });

		for (int i = 0; i < m_NrElementsFloor; i++)
		{
			m_pLevelFloor[i]->Draw();
		}

		int drawtree{};
		for (int i = 0; i < m_NrTrees / 3; i++)
		{
			switch (drawtree)
			{
			case 0:
				m_pLevelTreeA->Draw(m_posTree[i]);
				drawtree++;
				break;

			case 1:
				m_pLevelTreeB->Draw(m_posTree[i]);
				drawtree;
				break;

			case 2:
				m_pLevelTreeC->Draw(m_posTree[i]);
				drawtree = 0;
				break;

			default:
				break;
			}



		}


		m_Player1.Draw();

		for (int i = 0; i < m_NrElementsGrass; i++)
		{
			m_pLevelGrass[i]->Draw();
		}
		Color4f red{ 1.0f,0.0f,0.0f,0.80f };
		for (int i = 0; i < m_NrHL; i++)
		{
			dae::DrawFilledRect(m_HorizontalLasers[i], red);
		}
		for (int i = 0; i < m_NrVL; i++)
		{
			dae::DrawFilledRect(m_VerticalLasers[i], red);
		}
		for (int i = 0; i < m_NrGL; i++)
		{
			dae::DrawFilledRect(m_GroundLasers[i], red);
		}
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


void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		if (m_Player1.GetRunState() == Direction::Left)
		{
			m_Player1.SetRunState(Direction::Stationary);
		}
		
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		if (m_Player1.GetRunState() == Direction::Right)
		{
			m_Player1.SetRunState(Direction::Stationary);
		}
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

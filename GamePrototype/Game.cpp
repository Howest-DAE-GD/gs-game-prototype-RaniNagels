#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "iostream"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	PrintInstructions();
	m_Player = new Player(Point2f{ 120, GetViewPort().height / 2 });
	Actor::SetBoundaries(GetViewPort());
	m_Enemies.reserve(AMOUNT_OF_ENEMIES);
	m_Collectables.reserve(AMOUNT_OF_COLLECTABLES);
	for (int i{}; i < AMOUNT_OF_ENEMIES; ++i)
	{
		float y{ rand() % (int(GetViewPort().height) - 100) + 50.f };
		int delay{ rand() % 35 };
		m_Enemies.push_back(GameAssets{ Point2f{GetViewPort().width, y}, delay, type::enemie});
	}
	for (int i{}; i < AMOUNT_OF_COLLECTABLES; ++i)
	{
		float y{ rand() % (int(GetViewPort().height) - 100) + 50.f };
		int delay{ rand() % 35 };
		m_Collectables.push_back(GameAssets{ Point2f{GetViewPort().width, y}, delay, type::collectable });
	}
	m_GameOver = false;
}

void Game::Cleanup( )
{
	m_Enemies.clear();
	m_Collectables.clear();

	delete m_Player;
	m_Player = nullptr;
}

void Game::Reset()
{
	Cleanup();
	Initialize();
}

void Game::PrintInstructions()
{

}

void Game::ReuseGameAssets()
{
	for (int i{}; i < AMOUNT_OF_ENEMIES; ++i)
	{
		if (m_Enemies[i].GetIsKilled())
		{
			float y{ rand() % (int(GetViewPort().height) - 100) + 50.f };
			int delay{ rand() % 35 };
			m_Enemies[i] = GameAssets{ Point2f{GetViewPort().width, y}, delay, type::enemie };
			std::cout << "[ Enemy [" << i << "] RESET ]\n";
		}
	}

	for (int i{}; i < AMOUNT_OF_COLLECTABLES; ++i)
	{
		if (m_Collectables[i].GetIsKilled())
		{
			float y{ rand() % (int(GetViewPort().height) - 100) + 50.f };
			int delay{ rand() % 35 };
			m_Collectables[i] = GameAssets{ Point2f{GetViewPort().width, y}, delay, type::collectable };
			std::cout << "[ Collectable [" << i << "] RESET ]\n";
		}
	}
}

void Game::Update( float elapsedSec )
{
	if (m_GameOver == false)
	{
		m_Player->Update(elapsedSec);
		for (int i{}; i < AMOUNT_OF_ENEMIES; ++i)
		{
			m_Enemies[i].Update(elapsedSec);
			m_Player->HitDetection(&m_Enemies[i], type::enemie);
		}
		for (int i{}; i < AMOUNT_OF_COLLECTABLES; ++i)
		{
			m_Collectables[i].Update(elapsedSec);
			m_Player->HitDetection(&m_Collectables[i], type::collectable);
		}
		m_GameOver = m_Player->GameOver();
		ReuseGameAssets();
	}
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	if (m_GameOver == false)
	{
		ClearBackground();
		m_Player->Draw();

		for (int i{}; i < AMOUNT_OF_ENEMIES; ++i)
		{
			m_Enemies[i].Draw();
		}
		for (int i{}; i < AMOUNT_OF_COLLECTABLES; ++i)
		{
			m_Collectables[i].Draw();
		}
	}
	else
	{
		ClearBackground(Color4f{ 0.6f, 0.1f, 0.1f, 1.f });
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Player->ProcessKeyDownEvent(e);
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_Player->ProcessKeyUpEvent(e);
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_SPACE:
		if (m_GameOver)
		{
			Reset();
			std::cout << "RESET!\n";
		}
		break;
	//case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		//break;
	//case SDLK_1:
	//case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		//break;
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

void Game::ClearBackground(const Color4f& background_color) const
{
	glClearColor( background_color.r, background_color.g, background_color.b, background_color.a );
	glClear( GL_COLOR_BUFFER_BIT );
}

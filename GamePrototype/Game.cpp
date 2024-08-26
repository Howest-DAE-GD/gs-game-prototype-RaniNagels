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
	m_Boundaries = Rectf{ GetViewPort().width / 2 - DEFAULT_DIMENSIONS.x / 2, GetViewPort().height / 2 - DEFAULT_DIMENSIONS.y / 2, DEFAULT_DIMENSIONS.x, DEFAULT_DIMENSIONS.y };
	m_Player = new Player(Point2f{ 350, GetViewPort().height / 2 });
	Actor::SetBoundaries(m_Boundaries);
	InitializeForLoop(AMOUNT_OF_COLLECTABLES, m_Collectables, m_DirStateCollectables, type::collectable	);
	InitializeForLoop(AMOUNT_OF_ENEMIES     , m_Enemies     , m_DirStateEnemies     , type::enemie		);
	InitializeForLoop(AMOUNT_OF_SWITCHABLES , m_Switchables , m_DirStateSwitchables , type::switchable	);
	InitializeForLoop(AMOUNT_OF_BIGGERFIELD_POWERUPS	, m_BiggerField_PowerUps	, m_DirStateBiggerFieldPowerUps	, type::powerUp		);
	float y{ rand() % (int(m_Boundaries.height) - 100) + (GetViewPort().height - m_Boundaries.height) / 2 };
	int delay{ rand() % 70 };
	m_PowerUps.push_back(GameAssets{ Point2f{GetViewPort().width, y}, delay, powerUpType::SuperSpeed });
	y = rand() % (int(m_Boundaries.height) - 100) + (GetViewPort().height - m_Boundaries.height) / 2 ;
	delay = rand() % 70 ;
	m_PowerUps.push_back(GameAssets{ Point2f{GetViewPort().width, y}, 1, powerUpType::DoubleReward });
	m_DirSatePowerUps.push_back(false);
	m_DirSatePowerUps.push_back(false);
	m_GameOver = false;
	m_GameMode = gameMode::playing;

	m_pFont = TTF_OpenFont("DIN-Light.otf", 30);
	m_pSmallFont = TTF_OpenFont("DIN-Light.otf", 14);
	m_pDoubleTexture = new Texture{ "x2", m_pFont, Color4f{0.f, 0.f, 0.f} };
	m_pSmallDoubleTexture = new Texture{ "x2", m_pSmallFont, Color4f{0.f, 0.f, 0.f} };
	m_pSuperSpeedTexture = new Texture{ ">>", m_pFont, Color4f{0.f, 0.f, 0.f} };
	m_pSmallSuperSpeedTexture = new Texture{ ">>", m_pSmallFont, Color4f{0.f, 0.f, 0.f} };
	m_pPauseTexture = new Texture{ "PAUSE", m_pFont, Color4f{1.f,1.f,1.f} };
	Player::SetDoubleTexture(m_pDoubleTexture);
	Player::SetSuperSpeedTexture(m_pSuperSpeedTexture);
	GameAssets::SetDoubleTexture(m_pSmallDoubleTexture);
	GameAssets::SetSuperSpeedTexture(m_pSmallSuperSpeedTexture);
}

void Game::InitializeForLoop(int amount, std::vector<GameAssets>& assets, std::vector<bool>& dir_states, type type)
{
	assets.reserve(amount);
	for (int i{}; i < amount; ++i)
	{
		float y{ rand() % (int(m_Boundaries.height) - 100) + (GetViewPort().height - m_Boundaries.height)/2 };
		for (int r{}; r < i; ++r)
		{
			if (r != i)
			{
				while (assets[r].GetHitCircle().center.y <= y + 5 && assets[r].GetHitCircle().center.y >= y - 5)
				{
					y =  rand() % (int(GetViewPort().height) - 100) + (GetViewPort().height - m_Boundaries.height) / 2;
					switch (type)
					{
					case type::enemie:
						std::cout << "ENEMIE ";
						break;
					case type::collectable:
						std::cout << "COLLECTABLE ";
						break;
					case type::switchable:
						std::cout << "SWITCHABLE ";
						break;
					case type::powerUp:
						std::cout << "POWERUP ";
						break;
					}
					std::cout << "[" << i << "]: y reassignent\n";
				}
			}
		}
		if (type == type::powerUp)
		{
			int delay{ rand() % 150 };
			assets.push_back(GameAssets{ Point2f{GetViewPort().width, y}, delay, powerUpType::BiggerField });
		}
		else
		{
			int delay{ rand() % 35 };
			assets.push_back(GameAssets{ Point2f{GetViewPort().width, y}, delay, type });
		}
		dir_states.push_back(false);
	}
}

void Game::Cleanup( )
{
	m_Enemies.clear();
	m_Collectables.clear();
	m_Switchables.clear();
	m_BiggerField_PowerUps.clear();
	m_PowerUps.clear();

	delete m_Player;
	m_Player = nullptr;

	delete m_pDoubleTexture;
	m_pDoubleTexture = nullptr;

	delete m_pPauseTexture;
	m_pPauseTexture = nullptr;

	delete m_pSmallDoubleTexture;
	m_pSmallDoubleTexture = nullptr;

	delete m_pSuperSpeedTexture;
	m_pSuperSpeedTexture = nullptr;

	delete m_pSmallSuperSpeedTexture;
	m_pSmallSuperSpeedTexture = nullptr;
}

void Game::Reset()
{
	Cleanup();
	Initialize();
}

void Game::PrintInstructions()
{
	std::cout << "\t================= INSTRUCTIONS =================\n";
	std::cout << "\tUse the arrow keys to move the (blue) player.\n";
	std::cout << "\tThe GREEN ones add to your health,\n \tthe RED one decreases your health\n";
	std::cout << "\tThe YELLOW ones will add or decrease at random. They also have more value\n";
	std::cout << "\tYou can win by getting your speed to 0. The more points you gain the slower you go.\n";
	std::cout << "\tPress Space to restart if you are killed, or if you win.\n";
	std::cout << "\t================================================\n\n";
}

void Game::ReuseGameAssets(int amount, std::vector<GameAssets>& assets, std::vector<bool>& dir_states, type type)
{
	const int speedIncrease{ 35 };
	for (int i{}; i < amount; ++i)
	{
		if (assets[i].GetIsKilled())
		{
			const int delay{ rand() % 35 };
			Point2f pos{ 0,0 };
			if (!dir_states[i])
			{
				float x{ rand() % (int(m_Boundaries.width) - 100) + (GetViewPort().width - m_Boundaries.width)/2 };
				pos = Point2f{ x, GetViewPort().height};
			}
			else
			{
				float y{ rand() % (int(m_Boundaries.height) - 100) + (GetViewPort().height - m_Boundaries.height)/2 };
				pos = Point2f{ GetViewPort().width, y};
			}

			if (type == type::powerUp)
			{
				switch (assets[i].GetPowerUp())
				{
				case powerUpType::BiggerField:
					//assets[i] = GameAssets{ pos, delay, powerUpType::BiggerField };
					break;
				case powerUpType::SuperSpeed:
					assets[i] = GameAssets{ pos, delay, powerUpType::SuperSpeed };
					break;
				case powerUpType::catchNet:
					assets[i] = GameAssets{ pos, delay, powerUpType::catchNet };
					break;
				case powerUpType::DoubleReward:
					assets[i] = GameAssets{ pos, delay, powerUpType::DoubleReward };
					break;
				case powerUpType::DoubleRandom:
					assets[i] = GameAssets{ pos, delay, powerUpType::DoubleRandom };
					break;
				}
				
			}
			else
			{
				assets[i] = GameAssets{ pos, delay, type };
			}
			assets[i].SetSwitchDirection(!dir_states[i]);
			dir_states[i] = !dir_states[i];
			assets[i].SetSpeed(assets[i].GetSpeed() + speedIncrease);
		}
	}
}

void Game::Update( float elapsedSec )
{
	if (m_GameOver == false && m_GameMode == gameMode::playing)
	{
		m_Player->Update(elapsedSec);
		for (int i{}; i < AMOUNT_OF_ENEMIES; ++i)
		{
			m_Enemies[i].Update(elapsedSec);
			m_Player->HitDetection(&m_Enemies[i], type::enemie);
		}
		for (int i{}; i < AMOUNT_OF_COLLECTABLES; ++i)
		{
			if (m_Player->GetDoubleReward())
			{
				m_Collectables[i].SetPowerUpType(powerUpType::DoubleReward);
			}
			else
			{
				m_Collectables[i].SetPowerUpType(powerUpType::none);
			}
			m_Collectables[i].Update(elapsedSec);
			m_Player->HitDetection(&m_Collectables[i], type::collectable);
		}
		for (int i{}; i < AMOUNT_OF_SWITCHABLES; ++i)
		{
			m_Switchables[i].Update(elapsedSec);
			m_Player->HitDetection(&m_Switchables[i], type::switchable);
		}
		for (int i{}; i < AMOUNT_OF_BIGGERFIELD_POWERUPS; ++i)
		{
			m_BiggerField_PowerUps[i].Update(elapsedSec);
			m_Player->HitDetection(&m_BiggerField_PowerUps[i], type::powerUp, m_BiggerField_PowerUps[1].GetPowerUp());
		}
		for (int i{}; i < m_PowerUps.size(); ++i)
		{
			m_PowerUps[i].Update(elapsedSec);
			m_Player->HitDetection(&m_PowerUps[i], type::powerUp, m_PowerUps[i].GetPowerUp());
		}
		if (m_Player->CheckSpeedZero())
		{
			m_GameMode = gameMode::won;
		}

		Point2f offset{ (GetViewPort().width - DEFAULT_DIMENSIONS.x) / 6, (GetViewPort().height - DEFAULT_DIMENSIONS.y) / 6 };
		Point2f dimensions{ DEFAULT_DIMENSIONS.x+(offset.x*m_Player->GetIncreaseBoundaryAmount()), DEFAULT_DIMENSIONS.y+ (offset.y*m_Player->GetIncreaseBoundaryAmount())};
		m_Boundaries = Rectf{ GetViewPort().width / 2 - dimensions.x / 2, GetViewPort().height / 2 - dimensions.y / 2, dimensions.x, dimensions.y };
		Actor::SetBoundaries(m_Boundaries);

		ReuseGameAssets(AMOUNT_OF_ENEMIES, m_Enemies, m_DirStateEnemies, type::enemie);
		ReuseGameAssets(AMOUNT_OF_COLLECTABLES, m_Collectables, m_DirStateCollectables, type::collectable);
		ReuseGameAssets(AMOUNT_OF_SWITCHABLES, m_Switchables, m_DirStateSwitchables, type::switchable);
		ReuseGameAssets(AMOUNT_OF_BIGGERFIELD_POWERUPS, m_BiggerField_PowerUps, m_DirStateBiggerFieldPowerUps, type::powerUp);
		ReuseGameAssets(m_PowerUps.size(), m_PowerUps, m_DirSatePowerUps, type::powerUp);

		m_GameOver = m_Player->GameOver();
		if (m_GameOver)
		{
			m_GameMode = gameMode::lost;
		}
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

void Game::Draw() const
{
	if (m_GameMode == gameMode::playing || m_GameMode == gameMode::pause)
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
		for (int i{}; i < AMOUNT_OF_SWITCHABLES; ++i)
		{
			m_Switchables[i].Draw();
		}
		for (int i{}; i < AMOUNT_OF_BIGGERFIELD_POWERUPS; ++i)
		{
			m_BiggerField_PowerUps[i].Draw();
		}
		for (int i{}; i < m_PowerUps.size(); ++i)
		{
			m_PowerUps[i].Draw();
		}

		utils::SetColor(Color4f{ 1.f,0.f,0.f });
		utils::DrawRect(m_Boundaries, 4.f);

		if (m_GameMode == gameMode::pause)
		{
			Point2f pausePos{ GetViewPort().width / 2 - m_pPauseTexture->GetWidth() / 2, GetViewPort().height / 2 - m_pPauseTexture->GetHeight() / 2 };
			m_pPauseTexture->Draw(pausePos);
		}
	}
	else if (m_GameMode == gameMode::lost)
	{
		ClearBackground(Color4f{ 0.6f, 0.1f, 0.1f, 1.f });
	}
	else if (m_GameMode == gameMode::won)
	{
		ClearBackground(Color4f{ 0.1f, 0.6f, 0.1f, 1.f });
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
		if (m_GameMode == gameMode::won || m_GameMode == gameMode::lost)
		{
			Reset();
			std::cout << "RESET!\n";
		}
		else if (m_GameMode == gameMode::playing)
		{
			m_GameMode = gameMode::pause;
			std::cout << "PAUSE!\n";
		}
		else if (m_GameMode == gameMode::pause)
		{
			m_GameMode = gameMode::playing;
			std::cout << "PLAY!\n";
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

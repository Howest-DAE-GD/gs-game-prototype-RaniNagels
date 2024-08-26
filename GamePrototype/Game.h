#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "GameAssets.h"
#include <vector>

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	const int AMOUNT_OF_ENEMIES{ 20 };
	std::vector<GameAssets> m_Enemies;
	std::vector<bool> m_DirStateEnemies;
	const int AMOUNT_OF_COLLECTABLES{ 10 };
	std::vector<GameAssets> m_Collectables;
	std::vector<bool> m_DirStateCollectables;
	const int AMOUNT_OF_SWITCHABLES{ 10 };
	std::vector<GameAssets> m_Switchables;
	std::vector<bool> m_DirStateSwitchables;
	const int AMOUNT_OF_BIGGERFIELD_POWERUPS{ 5 };
	std::vector<GameAssets> m_BiggerField_PowerUps;
	std::vector<bool> m_DirStateBiggerFieldPowerUps;
	const int AMOUNT_OF_POWERUPS{4};
	std::vector<GameAssets> m_PowerUps;
	std::vector<bool> m_DirSatePowerUps;

	const Point2f DEFAULT_DIMENSIONS{ 700,500 };
	Rectf m_Boundaries;

	Player* m_Player;

	bool m_GameOver;
	gameMode m_GameMode{};
	

	TTF_Font* m_pFont;
	TTF_Font* m_pSmallFont;
	Texture* m_pDoubleTexture;
	Texture* m_pSmallDoubleTexture;
	Texture* m_pSuperSpeedTexture;
	Texture* m_pSmallSuperSpeedTexture;

	Texture* m_pPauseTexture;
	Texture* m_pTotalScore;

	// FUNCTIONS
	void Initialize();
	void PrintInstructions();
	void Cleanup( );
	void ClearBackground(const Color4f& background_color = Color4f{0.f, 0.f, 0.3f, 1.f}) const;
	void Reset();
	void ReuseGameAssets(int amount, std::vector<GameAssets>& assets, std::vector<bool>& dir_states, type type);
	void InitializeForLoop(int amount, std::vector<GameAssets>& assets, std::vector<bool>& dir_states, type type);
};
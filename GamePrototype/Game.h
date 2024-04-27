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
	const int AMOUNT_OF_ENEMIES{ 10 };
	std::vector<GameAssets> m_Enemies;
	const int AMOUNT_OF_COLLECTABLES{ 10 };
	std::vector<GameAssets> m_Collectables;
	Player* m_Player;
	bool m_GameOver;

	// FUNCTIONS
	void Initialize();
	void PrintInstructions();
	void Cleanup( );
	void ClearBackground(const Color4f& background_color = Color4f{0.f, 0.f, 0.3f, 1.f}) const;
	void Reset();
	void ReuseGameAssets();
};
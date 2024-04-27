#pragma once
#include "Actor.h"

class GameAssets;

class Player :
    public Actor
{
public:
    Player(const Point2f& pos);
    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;

    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

    void HitDetection(GameAssets* asset, type type);
    bool GameOver();

private:
    Rectf m_HitRect;
    void PrintHealth();
};


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

    void HitDetection(GameAssets* asset, type type, powerUpType powerUpType = powerUpType::none);
    bool GameOver();
    bool CheckSpeedZero();

    void SetSuperSpeedTexture(Texture* texture);

private:
    Rectf m_HitRect;
    int m_BaseSize;
    int m_BaseSpeed;
    bool m_SuperSpeed;
    float m_SuperSpeedCounter;
    const float SUPERSPEED_MAXTIME{7};
    Texture* m_pSuperSpeedTexture;
    int m_IncreaseBoundary; // 0 no increase, 1 little increase, 2 more etc
    void PrintHealth();
};


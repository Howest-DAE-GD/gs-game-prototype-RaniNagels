#pragma once
#include "Actor.h"

class GameAssets;

class Player :
    public Actor
{
public:
    Player(const Point2f& pos);
    virtual void Draw() const override;
    void DrawTimers() const;
    virtual void Update(float elapsedSec) override;
    void UpdateTimers(float elapsedSec);

    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

    void HitDetection(GameAssets* asset, type type, powerUpType powerUpType = powerUpType::none);
    bool GameOver();
    bool CheckSpeedZero();

    int GetIncreaseBoundaryAmount();
    bool GetDoubleReward();

    static void SetDoubleTexture(Texture* const texture_pointer);
    static void SetSuperSpeedTexture(Texture* const texture_pointer);

    int GetTotalScore() const;

private:
    static Texture* m_pDoubleTexture;
    static Texture* m_pSuperSpeedTexture;

    Rectf m_HitRect;
    int m_BaseSize;
    int m_BaseSpeed;
    bool m_SuperSpeed;
    bool m_DoubleReward;
    float m_SuperSpeedCounter;
    float m_DoubleRewardCounter;
    const float SUPERSPEED_MAXTIME{7};
    const float DOUBLEREWARD_MAXTIME{ 5 };
    int m_IncreaseBoundary; // 0 no increase, 1 little increase, 2 more etc
    void PrintHealth();

    Rectf m_DoubleTimer;
    Rectf m_SpeedTimer;

    int m_TotalScore;
};


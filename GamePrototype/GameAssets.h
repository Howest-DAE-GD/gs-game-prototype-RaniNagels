#pragma once
#include "Actor.h"

class GameAssets :
    public Actor
{
public:
    GameAssets(const Point2f& position, int delay, type type);

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;

    Circlef GetHitCircle() const;
    int GetDamage() const;
    void SetIsKilled(bool killed);
    bool GetIsKilled();

private:
    type m_Type;
    int m_Delay;
    float m_PassedSeconds;
    int m_HealthModifier;
    bool m_IsActive;
    bool m_IsKilled;
};


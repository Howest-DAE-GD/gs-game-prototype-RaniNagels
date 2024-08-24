#pragma once
#include "Actor.h"

class PowerUp :
    public Actor
{
public:
    explicit PowerUp(const Point2f& pos, powerUpType state);

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
private:
    powerUpType m_PowerUp;
    float duration;
};


#pragma once
#include "Actor.h"

class GameAssets :
    public Actor
{
public:
    GameAssets(const Point2f& position, int delay, type type, powerUpType powerUpType = powerUpType::none);
    GameAssets(const Point2f& position, int delay, powerUpType powerUpType);

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;

    Circlef GetHitCircle() const;
    int GetDamage() const;
    powerUpType GetPowerUp() const;
    void SetPowerUpType(const powerUpType& power_up_type);

    void SetIsKilled(bool killed);
    bool GetIsKilled() const;

    void SetSpeed(int speed);
    int GetSpeed() const;

    void SetSwitchDirection(bool isSwitch);
    bool GetSwitchDirection();

    static void SetDoubleTexture(Texture* const texture_pointer);
    static void SetSuperSpeedTexture(Texture* const texture_pointer);

private:
    static Texture* m_pDoubleTexture;
    static Texture* m_pSuperSpeedTexture;

    type m_Type;
    powerUpType m_PowerUpType;
    int m_Delay;
    float m_PassedSeconds;
    int m_HealthModifier;
    bool m_IsActive;
    bool m_IsKilled;
    bool m_SwitchDirection;
};


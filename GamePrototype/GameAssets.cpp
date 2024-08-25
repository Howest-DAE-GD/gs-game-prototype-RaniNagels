#include "pch.h"
#include "GameAssets.h"
#include "utils.h"

GameAssets::GameAssets(const Point2f& position, int delay, type type, powerUpType powerUpType)
	: Actor(position), m_IsActive{ false }, m_HealthModifier{}
	, m_Delay{ delay }, m_PassedSeconds{ 0 }, m_Type{type}
	, m_IsKilled{ false }, m_SwitchDirection{ false }
	, m_PowerUpType{ powerUpType }
{
	switch (m_Type)
	{
	case type::enemie:
		m_FillColor = utils::ConvertColor(152, 37, 15);
		m_EdgeColor = utils::ConvertColor(123, 30, 12);
		m_HealthModifier = int(rand() % 3 + 1);
		break;
	case type::collectable:
		m_FillColor = utils::ConvertColor(20, 135, 45);
		m_EdgeColor = utils::ConvertColor(15, 94, 32);
		m_HealthModifier = int(rand() % 2 + 1);
		break;
	case type::switchable:
		m_FillColor = utils::ConvertColor(183, 194, 25);
		m_EdgeColor = utils::ConvertColor(89, 94, 20);
		m_HealthModifier = int(rand() % 3 + 2);
		break;
	case type::powerUp:
		m_FillColor = utils::ConvertColor(200, 200, 200);
		m_EdgeColor = utils::ConvertColor(255, 255, 255);
		m_HealthModifier = 0;
		break;
	}
	m_Size = 50.f + (10 * m_HealthModifier);
	if (m_Type == type::powerUp)
	{
		m_Size = 40.f;
	}
	m_Speed = rand()%41 + 70;
	m_Health = 1;
}

GameAssets::GameAssets(const Point2f& position, int delay, powerUpType powerUpType)
	: GameAssets(position, delay, type::powerUp, powerUpType)
{
}

void GameAssets::Draw() const
{
	if (m_IsActive && m_IsKilled == false)
	{
		utils::SetColor(m_FillColor);
		utils::FillEllipse(m_Position, m_Size / 2.f, m_Size / 2.f);

		utils::SetColor(m_EdgeColor);
		utils::DrawEllipse(m_Position, m_Size / 2.f, m_Size / 2.f, 4);
		if (m_PowerUpType == powerUpType::DoubleReward || m_IsDouble)
		{
			m_pTexture->Draw(m_Position);
		}
	}

	Actor::Draw();
}

void GameAssets::Update(float elapsedSec)
{
	m_PassedSeconds += elapsedSec;
	if (m_Delay != -1)
	{
		if (m_PassedSeconds > m_Delay)
		{
			m_IsActive = true;
			m_Delay = -1;
		}
	}

	if (m_IsActive && m_IsKilled == false)
	{
		if (m_SwitchDirection == false)
		{
			if (m_Position.x + m_Size / 2 > m_Boundaries.left)
			{
				m_Position.x -= m_Speed * elapsedSec;
			}
			else
			{
				m_IsKilled = true;
			}
		}
		else
		{
			if (m_Position.y + m_Size / 2 > m_Boundaries.bottom)
			{
				m_Position.y -= m_Speed * elapsedSec;
			}
			else 
			{
				m_IsKilled = true;
			}
		}
	}
}

Circlef GameAssets::GetHitCircle() const
{
	return Circlef(m_Position, m_Size / 2);
}

int GameAssets::GetDamage() const
{
	return m_HealthModifier;
}

powerUpType GameAssets::GetPowerUp() const
{
	return m_PowerUpType;
}

void GameAssets::SetIsKilled(bool killed)
{
	m_IsKilled = killed;
}

bool GameAssets::GetIsKilled() const
{
	return m_IsKilled;
}

void GameAssets::SetSpeed(int speed)
{
	m_Speed = speed;
}

int GameAssets::GetSpeed() const
{
	return m_Speed;
}

void GameAssets::SetSwitchDirection(bool isSwitch)
{
	m_SwitchDirection = isSwitch;
}

bool GameAssets::GetSwitchDirection()
{
	return m_SwitchDirection;
}

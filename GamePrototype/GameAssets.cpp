#include "pch.h"
#include "GameAssets.h"
#include "utils.h"

GameAssets::GameAssets(const Point2f& position, int delay, type type)
	: Actor(position), m_IsActive{ false }, m_HealthModifier{}
	, m_Delay{ delay }, m_PassedSeconds{ 0 }, m_Type{type}
	, m_IsKilled{ false }, m_SwitchDirection{ false }
{
	switch (m_Type)
	{
	case type::enemie:
		m_FillColor = ConvertColor(152, 37, 15);
		m_EdgeColor = ConvertColor(123, 30, 12);
		m_HealthModifier = int(rand() % 3 + 1);
		break;
	case type::collectable:
		m_FillColor = ConvertColor(20, 135, 45);
		m_EdgeColor = ConvertColor(15, 94, 32);
		m_HealthModifier = int(rand() % 2 + 1);
		break;
	case type::switchable:
		m_FillColor = ConvertColor(183, 194, 25);
		m_EdgeColor = ConvertColor(89, 94, 20);
		m_HealthModifier = int(rand() % 3 + 2);
		break;
	}
	m_Size = 50.f + (10 * m_HealthModifier);
	m_Speed = rand()%41 + 70;
	m_Health = 1;
}

void GameAssets::Draw() const
{
	if (m_IsActive && m_IsKilled == false)
	{
		utils::SetColor(m_FillColor);
		utils::FillEllipse(m_Position, m_Size / 2.f, m_Size / 2.f);

		utils::SetColor(m_EdgeColor);
		utils::DrawEllipse(m_Position, m_Size / 2.f, m_Size / 2.f, 4);
	}
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

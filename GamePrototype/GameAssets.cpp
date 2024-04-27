#include "pch.h"
#include "GameAssets.h"
#include "utils.h"

GameAssets::GameAssets(const Point2f& position, int delay, type type)
	: Actor(position), m_HealthModifier{1}, m_IsActive{false}
	, m_Delay{ delay }, m_PassedSeconds{ 0 }, m_Type{type}
	, m_IsKilled{false}
{
	switch (m_Type)
	{
	case type::enemie:
		m_FillColor = ConvertColor(152, 37, 15);
		m_EdgeColor = ConvertColor(123, 30, 12);
		break;
	case type::collectable:
		m_FillColor = ConvertColor(183, 194, 25);
		m_EdgeColor = ConvertColor(89, 94, 20);
		break;
	}
	m_Size = 45;
	m_Speed = 80;
	m_Health = 1;
}

void GameAssets::Draw() const
{
	if (m_IsActive && m_IsKilled == false)
	{
		utils::SetColor(m_FillColor);
		utils::FillEllipse(m_Position, m_Size / 2, m_Size / 2);

		utils::SetColor(m_EdgeColor);
		utils::DrawEllipse(m_Position, m_Size / 2, m_Size / 2, 4);
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
		if (m_Position.x + m_Size / 2 > m_Boundaries.left)
		{
			m_Position.x -= m_Speed * elapsedSec;
		}
		else
		{
			m_IsKilled = true;
		}
	}
}

Circlef GameAssets::GetHitCircle() const
{
	return Circlef(m_Position, m_Size / 3);
}

int GameAssets::GetDamage() const
{
	return m_HealthModifier;
}

void GameAssets::SetIsKilled(bool killed)
{
	m_IsKilled = killed;
}

bool GameAssets::GetIsKilled()
{
	return m_IsKilled;
}

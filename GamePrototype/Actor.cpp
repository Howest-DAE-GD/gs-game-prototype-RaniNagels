#include "pch.h"
#include "Actor.h"

Rectf Actor::m_Boundaries{};

Actor::Actor(const Point2f& pos)
	: m_Position{ pos }, m_Size{}, m_Speed{}, m_Health{},
	m_FillColor{}, m_EdgeColor{}, m_IsDouble{false}
{
}

void Actor::Draw() const
{
	
}

void Actor::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

void Actor::SetDoubleState(bool is_double)
{
	m_IsDouble = is_double;
}

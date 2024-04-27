#include "pch.h"
#include "Actor.h"

Rectf Actor::m_Boundaries{};

Actor::Actor(const Point2f& pos)
	: m_Position{ pos }, m_Size{}, m_Speed{}, m_Health{},
	m_FillColor{}, m_EdgeColor{}
{
}

void Actor::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

Color4f Actor::ConvertColor(int r, int g, int b)
{
	float max{ 255.f };
	return Color4f(r/max, g/max, b/max, 1.f);
}

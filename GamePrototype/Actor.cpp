#include "pch.h"
#include "Actor.h"

Actor::Actor(const Point2f& pos, const Rectf& boundaries)
	: m_Position{ pos }, m_Size{}, m_Speed{},
	m_FillColor{}, m_EdgeColor{}, m_Boundaries{boundaries}
{
}

Color4f Actor::ConvertColor(int r, int g, int b)
{
	float max{ 255.f };
	return Color4f(r/max, g/max, b/max, 1.f);
}

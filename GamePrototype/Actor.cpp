#include "pch.h"
#include "Actor.h"

Rectf Actor::m_Boundaries{};
Texture* Actor::m_pTexture{nullptr};

Actor::Actor(const Point2f& pos)
	: m_Position{ pos }, m_Size{}, m_Speed{}, m_Health{},
	m_FillColor{}, m_EdgeColor{}, m_IsDouble{false}
{
}

void Actor::Draw() const
{
	if (m_IsDouble)
	{
		if (m_pTexture != nullptr && m_pTexture->IsCreationOk())
		{
			m_pTexture->Draw(Point2f{m_Position.x - m_pTexture->GetWidth()/2, m_Position.y - m_pTexture->GetHeight()/2});
		}
	}
}

void Actor::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

void Actor::SetDoubleTexture(Texture* const texture_pointer)
{
	m_pTexture = texture_pointer;
}

void Actor::SetDoubleState(bool is_double)
{
	m_IsDouble = is_double;
}

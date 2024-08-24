#include "pch.h"
#include "PowerUp.h"
#include "utils.h"

PowerUp::PowerUp(const Point2f& pos, powerUpType state)
	: Actor(pos), m_PowerUp{state}, duration{}
{
}

void PowerUp::Draw() const
{
	utils::SetColor(Color4f{ 1.f, 1.f, 1.f });
	utils::DrawEllipse(m_Position, m_Size, m_Size, 5.f);
}

void PowerUp::Update(float elapsedSec)
{
}

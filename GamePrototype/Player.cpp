#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "iostream"

Player::Player(const Point2f& pos, const Rectf& boundaries)
	: Actor(pos, boundaries)
{
	m_FillColor = ConvertColor(20, 104, 152);
	m_EdgeColor = ConvertColor(17, 87, 128);
	m_Size = 60;
	m_Speed = 250;
}

void Player::Draw() const
{
	Point2f center{ m_Position.x - m_Size / 2, m_Position.y - m_Size / 2 };

	utils::SetColor(m_FillColor);
	utils::FillRect(center, m_Size, m_Size);

	utils::SetColor(m_EdgeColor);
	utils::DrawRect(center, m_Size, m_Size, 5);
}

void Player::Update(float elapsedSec)
{
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_UP])
	{
		if (m_Position.y + m_Size / 2 < m_Boundaries.height)
		{
			m_Position.y += m_Speed * elapsedSec;
		}
	}
	if ( pStates[SDL_SCANCODE_DOWN] )
	{
		if (m_Position.y - m_Size / 2 > m_Boundaries.bottom)
		{
			m_Position.y -= m_Speed * elapsedSec;
		}
	}
}

void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//switch (e.keysym.sym)
	//{
	//case SDLK_UP:
	//	if (m_Position.y + m_Size/2 < m_Boundaries.height)
	//	{
	//		m_Velocity.y = m_Speed;
	//	}
	//	else
	//	{
	//		m_Velocity.y = 0;
	//	}
	//	break;
	//case SDLK_DOWN:
	//	m_Velocity.y = -m_Speed;
	//	break;
	//}
}

void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//switch (e.keysym.sym)
	//{
	//case SDLK_UP:
	//	break;
	//case SDLK_DOWN:
	//	break;
	//}
}

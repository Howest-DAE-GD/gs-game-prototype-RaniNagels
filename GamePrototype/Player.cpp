#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "iostream"
#include "GameAssets.h"

Player::Player(const Point2f& pos)
	: Actor(pos)
{
	m_FillColor = utils::ConvertColor(20, 104, 152);
	m_EdgeColor = utils::ConvertColor(17, 87, 128);
	m_SuperSpeed = false;
	m_SuperSpeedCounter = 0;
	m_Health = 5;
	m_BaseSize = 12;
	m_BaseSpeed = 20;
	m_Size = 40.f + m_BaseSize * m_Health;
	m_Speed = 430 - m_BaseSpeed * m_Health;
	m_HitRect = Rectf{ m_Position.x - m_Size / 2, m_Position.y - m_Size / 2 , float(m_Size), float(m_Size) };
	m_pSuperSpeedTexture = nullptr;
	m_IncreaseBoundary = 0;
}

void Player::Draw() const
{
	if (m_Health > 0)
	{
		Point2f center{ m_Position.x - m_Size / 2, m_Position.y - m_Size / 2 };

		utils::SetColor(m_FillColor);
		utils::FillRect(center, m_Size, m_Size);

		utils::SetColor(m_EdgeColor);
		utils::DrawRect(center, m_Size, m_Size, 5);
		
		if (m_SuperSpeed && m_pSuperSpeedTexture != nullptr)
		{
			m_pSuperSpeedTexture->Draw(Point2f{m_Position.x - m_Size/2, m_Position.y});
		}
	}

	Actor::Draw();

}

void Player::Update(float elapsedSec)
{
	int speed = m_Speed;
	if (m_Health > 0)
	{
		if (m_SuperSpeed)
		{
			if (m_SuperSpeedCounter >= SUPERSPEED_MAXTIME)
			{
				m_SuperSpeed = false;
				m_SuperSpeedCounter = 0;
				std::cout << "SUPERSPEED DEACTIVATED!!\n";
			}
			else
			{
				speed += 250;
				m_SuperSpeedCounter += elapsedSec;
			}
		}
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W])
		{
			if (m_Position.y + m_Size / 2 < m_Boundaries.height + m_Boundaries.bottom)
			{
				m_Position.y += speed * elapsedSec;
			}
		}
		if (pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S])
		{
			if (m_Position.y - m_Size / 2 > m_Boundaries.bottom)
			{
				m_Position.y -= speed * elapsedSec;
			}
		}
		if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
		{
			if (m_Position.x - m_Size / 2 > m_Boundaries.left)
			{
				m_Position.x -= speed * elapsedSec;
			}
		}
		if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D])
		{
			if (m_Position.x + m_Size / 2 < m_Boundaries.width + m_Boundaries.left)
			{
				m_Position.x += speed * elapsedSec;
			}
		}
		m_HitRect = Rectf{ m_Position.x - m_Size / 2, m_Position.y - m_Size / 2 , float(m_Size), float(m_Size) };
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

void Player::HitDetection(GameAssets* asset, type type, powerUpType powerUpType)
{
	if (asset->GetIsKilled() == false)
	{
		if (utils::IsOverlapping(m_HitRect, asset->GetHitCircle()))
		{
			switch (type)
			{
			case type::enemie:
				m_Health -= asset->GetDamage();
				break;
			case type::collectable:
				m_Health += asset->GetDamage();
				break;
			case type::powerUp:
				switch (powerUpType)
				{
				case powerUpType::SuperSpeed:
					m_SuperSpeed = true;
					m_SuperSpeedCounter = 0;
					break;
				case powerUpType::BiggerField:
					++m_IncreaseBoundary;
					break;
				}
				break;
			case type::switchable:
				int random{ rand() % 2 };
				if (random == 0)
				{
					m_Health += asset->GetDamage();
				}
				else
				{
					m_Health -= asset->GetDamage();
				}
				break;
			}
			m_Speed = 430 - m_BaseSpeed * m_Health;
			m_Size = 40.f + m_BaseSize * m_Health;
			PrintHealth();
			asset->SetIsKilled(true);
		}
	}
}

bool Player::GameOver()
{
	if (m_Health > 0)
	{
		return false;
	}
	std::cout << "[ GAME OVER ] : Press Space to restart\n";
	return true;
}

bool Player::CheckSpeedZero()
{
	if (m_Speed <= 0)
	{
		return true;
	}
	return false;
}

void Player::SetSuperSpeedTexture(Texture* texture)
{
	m_pSuperSpeedTexture = texture;
}

void Player::PrintHealth()
{
	std::cout << "[HEALTH]: " << m_Health << "\t [SPEED]: " << m_Speed << std::endl;
}

#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "iostream"
#include "GameAssets.h"

Texture* Player::m_pDoubleTexture{ nullptr };
Texture* Player::m_pSuperSpeedTexture{ nullptr };

Player::Player(const Point2f& pos)
	: Actor(pos)
{
	m_FillColor = utils::ConvertColor(20, 104, 152);
	m_EdgeColor = utils::ConvertColor(17, 87, 128);
	m_SuperSpeed = false;
	m_SuperSpeedCounter = 0;
	m_DoubleReward = false;
	m_DoubleRewardCounter = 0;
	m_Health = 5;
	m_BaseSize = 12;
	m_BaseSpeed = 20;
	m_Size = 40.f + m_BaseSize * m_Health;
	m_Speed = 430 - m_BaseSpeed * m_Health;
	m_HitRect = Rectf{ m_Position.x - m_Size / 2, m_Position.y - m_Size / 2 , float(m_Size), float(m_Size) };
	m_IncreaseBoundary = 0;
	m_DoubleTimer = Rectf{ 100, 30, 0, 30 };
	m_SpeedTimer  = Rectf{ 100, 70, 0, 30 };
	m_TotalScore = 0;
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
			m_pSuperSpeedTexture->Draw(Point2f{m_Position.x - m_Size/2, m_Position.y + m_Size/6});
		}
		if (m_DoubleReward)
		{
			m_pDoubleTexture->Draw(Point2f{ m_Position.x - m_Size / 2, m_Position.y - m_Size/3});
		}
	}

}

void Player::DrawTimers() const
{
	utils::SetColor(Color4f{ 0.6f, 0.6f, 0.6f });
	utils::FillRect(m_DoubleTimer);
	utils::FillRect(m_SpeedTimer);

	utils::SetColor(Color4f{ 0.8f, 0.8f, 0.8f });
	utils::DrawRect(Rectf{ 100, 30, 200, 30 });
	utils::DrawRect(Rectf{ 100, 70, 200, 30 });
	m_pDoubleTexture->Draw(Point2f{ 20, 30 });
	m_pSuperSpeedTexture->Draw(Point2f{ 20, 70 });

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
		if (m_DoubleReward)
		{
			if (m_DoubleRewardCounter >= DOUBLEREWARD_MAXTIME)
			{
				m_DoubleReward = false;
				m_DoubleRewardCounter = 0;
				std::cout << "DOUBLE REWARD DEACTIVATED!!\n";
			}
			else
			{
				speed += 250;
				m_DoubleRewardCounter += elapsedSec;
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

void Player::UpdateTimers(float elapsedSec)
{
	if (m_DoubleReward)
	{
		float width{ 200 * ((DOUBLEREWARD_MAXTIME - m_DoubleRewardCounter)/ DOUBLEREWARD_MAXTIME) };
		m_DoubleTimer.width = width;
	}
	if (m_SuperSpeed)
	{
		float width{ 200 * ((SUPERSPEED_MAXTIME - m_SuperSpeedCounter) / SUPERSPEED_MAXTIME) };
		m_SpeedTimer.width = width;
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
				if (m_DoubleReward)
				{
					m_TotalScore += asset->GetDamage();
					m_Health += asset->GetDamage();
				}
				m_TotalScore += asset->GetDamage();
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
				case powerUpType::DoubleReward:
					m_DoubleReward = true;
					m_DoubleRewardCounter = 0;
					break;
				}
				break;
			case type::switchable:
				int random{ rand() % 2 };
				if (random == 0)
				{
					m_TotalScore += asset->GetDamage();
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

int Player::GetIncreaseBoundaryAmount()
{
	if (m_IncreaseBoundary < 6)
	{
		return m_IncreaseBoundary;
	}
	else
	{
		return 6;
	}
}

bool Player::GetDoubleReward()
{
	return m_DoubleReward;
}

void Player::PrintHealth()
{
	std::cout << "[HEALTH]: " << m_Health << "\t [SPEED]: " << m_Speed << "\t [TOTAL SCORE]: " << m_TotalScore << std::endl;
}

void Player::SetDoubleTexture(Texture* const texture_pointer)
{
	m_pDoubleTexture = texture_pointer;
}

void Player::SetSuperSpeedTexture(Texture* const texture_pointer)
{
	m_pSuperSpeedTexture = texture_pointer;
}

int Player::GetTotalScore() const
{
	return m_TotalScore;
}

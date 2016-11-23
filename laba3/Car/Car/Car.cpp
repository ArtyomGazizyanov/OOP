#include "stdafx.h"

#include "Car.h"
#include "AbilityToSwitchGears.h"
#include "CarController.h"
 
bool CCar::IsEngineOn()const
{
	return m_isTurnOn;
}

bool CCar::TurnOnEngine()
{
	if (m_isTurnOn)
	{
		return false;
	}
	m_isTurnOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_currentGear == Gear::NEUTRAL && m_isTurnOn && m_speed == 0)
	{
		m_isTurnOn = false;
		return true;
	}
	return false;
}
  
bool CCar::SetGear(int gear)
{
	if (!m_isTurnOn && gear != 0)
	{
		return false;
	}
	if (!m_isTurnOn && gear == 0)
	{
		return true;
	}
	if (m_isTurnOn && (gear >= -1) && (gear <= 5))
	{
		switch (gear)
		{
		case -1:
			return CanSetReverseGear(m_speed, m_currentGear);

		case 0: 
			return CanSetNeutralGear(m_currentGear);

		case 1: 
			return CanSetFirstGear(m_direction, m_speed, m_currentGear);

		case 2:
			return CanSetSecondGear(m_speed, m_currentGear);

		case 3:
			return CanSetThirdGear(m_speed, m_currentGear);

		case 4:			
			return CanSetFourthGear(m_speed, m_currentGear);
			
		case 5: 
			return CanSetFifthGear(m_speed, m_currentGear);;
		}
		return false;
	}
	else
	{
		return false;
	}
}

int CCar::GetCurrnetSpeed() const
{
	return m_speed;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isTurnOn)
	{
		return false;
	}
	if (m_currentGear == Gear::REVERSE && speed >= 0 && speed <= 20)
	{
		m_speed = speed;
		m_speed > 0 ? m_direction = Direction::BACKWARD : m_direction = Direction::STAY;
		return true;
	}
	else if (m_currentGear == Gear::NEUTRAL && speed < m_speed)
	{
		m_speed = speed;
		if (m_speed == 0)
		{
			m_direction = Direction::STAY;
		}
		return true;
	}
	else if (m_currentGear == Gear::FIRST && speed >= 0 && speed <= 30)
	{
		m_speed = speed;
		m_direction = Direction::FORWARD;
		return true;
	}
	else if (m_currentGear == Gear::SECOND && speed >= 20 && speed <= 50)
	{
		m_speed = speed;
		m_direction = Direction::FORWARD;
		return true;
	}
	else if (m_currentGear == Gear::THIRD && speed >= 30 && speed <= 60)
	{
		m_speed = speed;
		m_direction = Direction::FORWARD;
		return true;
	}
	else if (m_currentGear == Gear::FOURTH && speed >= 40 && speed <= 90)
	{
		m_speed = speed;
		m_direction = Direction::FORWARD;
		return true;
	}
	else if (m_currentGear == Gear::FIFTH && (speed >= 50 && speed <= 150))
	{
		m_speed = speed;
		m_direction = Direction::FORWARD;
		return true;
	}
	return false;
}

std::string CCar::GetCurrentDirection()const
{
	std::string direction;

	if (m_direction == Direction::FORWARD)
	{
		direction = "forward";
	}
	else if (m_direction == Direction::BACKWARD)
	{
		direction = "backward";
	}
	else if (m_direction == Direction::STAY)
	{
		direction = "stay";
	}
	return direction;
} 

int CCar::GetCurrentGear()const
{
	return static_cast<int>(m_currentGear);
}
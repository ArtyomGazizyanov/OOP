#pragma once

enum struct Gear
{
	REVERSE = -1,
	NEUTRAL = 0,
	FIRST = 1,
	SECOND = 2,
	THIRD = 3,
	FOURTH = 4,
	FIFTH = 5,
};

enum struct Direction
{
	BACKWARD = -1,
	STAY = 0,
	FORWARD = 1,
}; 

class CCar
{
public: 
	bool IsEngineOn()const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	int GetCurrentGear()const;
	int GetCurrnetSpeed()const;
	std::string GetCurrentDirection()const;
private:
	bool m_isTurnOn = false;
	Gear m_currentGear = Gear::NEUTRAL;
	Direction m_direction = Direction::STAY;
	int m_speed = 0;
};
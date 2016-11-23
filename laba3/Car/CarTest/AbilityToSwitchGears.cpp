#include "stdafx.h"
#include "../Car/AbilityToSwitchGears.h"
#include "../Car/Car.h"
#include "../Car/CarController.h"


bool CanSetReverseGear(int const &speed, Gear &currGear)
{
	if (speed == 0 && (currGear == Gear::NEUTRAL || currGear == Gear::FIRST))
	{
		currGear = Gear::REVERSE;
		return true;
	}
	return false;
}

bool CanSetNeutralGear(Gear &currGear)
{
	currGear = Gear::NEUTRAL;
	return true;
}

bool CanSetFirstGear(Direction const &direction, int const &speed, Gear &currGear)
{
	if ((currGear == Gear::REVERSE && speed == 0)
		|| (currGear == Gear::NEUTRAL && direction == Direction::STAY && speed >= 0 && speed <= 30)
		|| (direction == Direction::FORWARD && speed >= 0 && speed <= 30))
	{
		currGear = Gear::FIRST;
		return true;
	}
	return false;
}

bool CanSetSecondGear(int const &speed, Gear &currGear)
{
	if (speed >= 20 && speed <= 50)
	{
		currGear = Gear::SECOND;
		return true;
	}
	return false;
}

bool CanSetThirdGear(int const &speed, Gear &currGear)
{
	if (speed >= 30 && speed <= 60)
	{
		currGear = Gear::THIRD;
		return true;
	}
	return false;
}

bool CanSetFourthGear(int const &speed, Gear &currGear)
{
	if (speed >= 40 && speed <= 90)
	{
		currGear = Gear::FOURTH;
		return true;
	}
	return false;
}

bool CanSetFifthGear(int const &speed, Gear &currGear)
{
	if (speed >= 50 && speed <= 150)
	{
		currGear = Gear::FIFTH;
		return true;
	}
	return false;
}
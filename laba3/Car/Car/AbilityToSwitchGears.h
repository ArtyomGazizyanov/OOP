#pragma once 
#include "Car.h"
bool CanSetReverseGear(int const &speed, Gear &currGear);
bool CanSetNeutralGear(Gear &currGear);
bool CanSetFirstGear(Direction const &direction, int const &speed, Gear &currGear);
bool CanSetSecondGear(int const &speed, Gear &currGear);
bool CanSetThirdGear(int const &speed, Gear &currGear);
bool CanSetFourthGear(int const &speed, Gear &currGear);
bool CanSetFifthGear(int const &speed, Gear &currGear);
 
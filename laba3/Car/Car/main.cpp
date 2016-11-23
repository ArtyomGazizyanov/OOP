// main.cpp: определяет точку входа в приложение.
//

#include "stdafx.h"
//#include "Car.h"
//#include "CarController.h"

int main()
{
	setlocale(LC_ALL, "rus");
	CCar zazChance;
	CCarDriver carDriver(zazChance, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << ">> ";
		if (!carDriver.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}
	return 0;
}
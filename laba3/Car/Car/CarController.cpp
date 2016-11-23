#include "stdafx.h"  
#include "Car.h"
#include "CarController.h"

using namespace std;
using namespace std::placeholders;

CCarDriver::CCarDriver(CCar &car, std::istream &input, std::ostream &output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "Info", bind(&CCarDriver::Info, this, _1) },
	{ "EngineOn", bind(&CCarDriver::EngineOn, this, _1) },
	{ "EngineOff", bind(&CCarDriver::EngineOff, this, _1) },
	{ "SetGear", bind(&CCarDriver::SetGear, this, _1) },
	{ "SetSpeed", bind(&CCarDriver::SetSpeed, this, _1) }
})
{
}

bool CCarDriver::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream inputStream(commandLine);

	string action;
	inputStream >> action;

	auto currAction = m_actionMap.find(action);
	if (currAction != m_actionMap.end())
	{
		return currAction->second(inputStream);
	}
	return false;
}

bool CCarDriver::Info(std::istream & args)
{
	string info = (m_car.IsEngineOn())
		? ("Engine is turned on\nDirection: " + m_car.GetCurrentDirection() + "\nGear: " + to_string(m_car.GetCurrentGear())
			+ "\nSpeed: " + to_string(m_car.GetCurrnetSpeed()) + "\n")

		: "Engine is turned off\n";

	m_output << info;

	return true;
}

bool CCarDriver::EngineOn(std::istream & args)
{
	m_car.TurnOnEngine();
	return true;
}

bool CCarDriver::EngineOff(std::istream & args)
{
	m_car.TurnOffEngine();
	return true;
}

bool CCarDriver::SetGear(std::istream & args)
{
	int gear;
	args >> gear;
	if (!m_car.SetGear(gear))
	{
		string error = "Engine is turned off or gear does not match current speed\n";
		m_output << error;
	}
	return true;
}

bool CCarDriver::SetSpeed(std::istream & args)
{
	int speed;
	args >> speed;
	if (!m_car.SetSpeed(speed))
	{
		string error = "Speed is out of available range for " + to_string(m_car.GetCurrentGear()) + " gear\n";
		m_output << error;
	}
	return true;
}
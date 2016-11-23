#pragma once
#include "Stdafx.h"

class CCarDriver
{
public:
	CCarDriver(CCar & car, std::istream & input, std::ostream & output);
	bool HandleCommand(); 
private:
	bool Info(std::istream & args);
	bool EngineOn(std::istream & args);
	bool EngineOff(std::istream & args);
	bool SetGear(std::istream & args);
	bool SetSpeed(std::istream & args);

	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

	CCar & m_car;
	std::istream & m_input;
	std::ostream & m_output;

	ActionMap m_actionMap;
};

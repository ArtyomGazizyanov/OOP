#include "stdafx.h"
#include "../Car/CarController.h"
#include "../Car/Car.h"
#include <sstream> 
#include <boost/optional.hpp> 
 
 
struct CCarControllerDependencies
{
	CCar car;
	std::stringstream input;
	std::stringstream output;
};

struct CCarDriverFixture : CCarControllerDependencies
{
	CCarDriver remoteControl;

	CCarDriverFixture()
		: remoteControl(car, input, output)
	{
	} 
	void CheckComandsOperations(std::string const &command, std::string const &expectedAnswer)
	{ 
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedAnswer);
	}
};

BOOST_FIXTURE_TEST_SUITE(Car_driver, CCarDriverFixture)
 
	BOOST_AUTO_TEST_CASE(can_accept_EngineOn_command)
	{
		CheckComandsOperations("EngineOn", "");
	}

	BOOST_AUTO_TEST_CASE(can_accept_Info_command)
	{
		CheckComandsOperations("Info", "Engine is turned off\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_errors_message)
	{
		CheckComandsOperations("SetGear 1", "Engine is turned off or gear does not match current speed\n");
	}
	

BOOST_AUTO_TEST_SUITE_END()

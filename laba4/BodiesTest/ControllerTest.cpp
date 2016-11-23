#include "stdafx.h"
#include <sstream>
#include "../laba4/CBody.h"
#include "../laba4/BodiesController.h"


struct ControllerDependencies
{
	vector<shared_ptr<CBody>> bodies;
	stringstream input;
	stringstream output;
};

struct ControllerFixture : ControllerDependencies
{
	CController controller;

	ControllerFixture()
		: controller(bodies, input, output)
	{
	}

	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(controller.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void HandleCommand(const string& command)
	{
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(controller.HandleCommand()); 
	}

	void VerifyMaxFindingFunction(const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		HandleCommand("Sphere 5 10");
		HandleCommand("Sphere 40 20");
		HandleCommand("ShowBodyWithMaxMass");	
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void VerifySmallestWeightFincion(const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		HandleCommand("Sphere 5 10");
		HandleCommand("Cone 1000 20 100");
		HandleCommand("ShowBodyWithSmallestWeight");
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Controller, ControllerFixture)

	BOOST_AUTO_TEST_CASE(can_handle_sphere)
	{
		VerifyCommandHandling("Sphere 5 10", "");
	}
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_sphere)
	{
		VerifyCommandHandling("Sphere 5", "Invalid count of arguments\nUsage: Sphere <density> <radius>\n");
	}
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_parallelepiped)
	{
		VerifyCommandHandling("Parallelepiped 11 12",  "Invalid count of arguments\nUsage: Parallelepiped <width> <height> <depth> <density>\n");
	}
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_cone)
	{
		VerifyCommandHandling("Cone 12", "Invalid count of arguments\nUsage: Cone <density> <radius> <height>\n");
	}
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_cylinder)
	{
		VerifyCommandHandling("Cylinder 10 22 33", "");
	} 
	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		VerifyCommandHandling("Sphere -5 10", "Invalid arguments\nArguments must be >= 0!\n");
	}

	BOOST_AUTO_TEST_CASE(check_max_mass_function)
	{
		VerifyMaxFindingFunction("Body with MAX mass is Sphere:\n\tdensity = 40\n\tvolume = 33510.32164\n\tmass = 1340412.866\n\tradius = 20\n");
	}

	BOOST_AUTO_TEST_CASE(check_smallest_weight_function)
	{
		VerifySmallestWeightFincion("Body with SMALLEST weight is Sphere:\n\tdensity = 5\n\tvolume = 4188.790205\n\tmass = 20943.95102\n\tradius = 10\n");
	}
BOOST_AUTO_TEST_SUITE_END()

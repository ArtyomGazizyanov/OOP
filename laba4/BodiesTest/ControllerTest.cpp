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
	//функция для сверения результатов работы команды с ожидаемым выводом программы
	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(controller.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
	//функция для захвата коман
	void HandleCommand(const string& command)
	{
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(controller.HandleCommand()); 
	}
	//функция для проверки корректности работы функции по нахождению мах массы у тела
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
	//функция для проверки корректности работы функции по нахождению минимального веса у тела
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
	//программа должна принять комнду на создание сферы
	BOOST_AUTO_TEST_CASE(can_handle_sphere)
	{
		VerifyCommandHandling("Sphere 5 10", "");
	}
	//программа не должна принять комнду на создание сферы(не верные значения при задании фигуры)
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_sphere)
	{
		VerifyCommandHandling("Sphere 5", "Invalid count of arguments\nUsage: Sphere <density> <radius>\n");
	}
	//программа не должна принять комнду на создание параллелепипеда(не верные значения при задании фигуры)
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_parallelepiped)
	{
		VerifyCommandHandling("Parallelepiped 11 12",  "Invalid count of arguments\nUsage: Parallelepiped <width> <height> <depth> <density>\n");
	}
	//программа не должна принять комнду на создание конуса(не верные значения при задании фигуры)
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_cone)
	{
		VerifyCommandHandling("Cone 12", "Invalid count of arguments\nUsage: Cone <density> <radius> <height>\n");
	}
	//программа не должна принять комнду на создание цилиндра(не верные значения при задании фигуры)
	BOOST_AUTO_TEST_CASE(can_handle_invalid_input_for_cylinder)
	{
		VerifyCommandHandling("Cylinder 10 22 33", "");
	} 
	//программа не должна принять комнду на создание сферы(фигура не может быть здана отрицательными значениями)
	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		VerifyCommandHandling("Sphere -5 10", "Invalid arguments\nArguments must be >= 0!\n");
	}
	//проверка функции нахождения максимальной массы фигуры
	BOOST_AUTO_TEST_CASE(check_max_mass_function)
	{
		VerifyMaxFindingFunction("Body with MAX mass is Sphere:\n\tdensity = 40\n\tvolume = 33510.32164\n\tmass = 1340412.866\n\tradius = 20\n");
	}
	//проверка функции нахождения минимального веса фигуры
	BOOST_AUTO_TEST_CASE(check_smallest_weight_function)
	{
		VerifySmallestWeightFincion("Body with SMALLEST weight is Sphere:\n\tdensity = 5\n\tvolume = 4188.790205\n\tmass = 20943.95102\n\tradius = 10\n");
	}
BOOST_AUTO_TEST_SUITE_END()

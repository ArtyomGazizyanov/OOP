#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../laba4/CParallelepiped.h"
#include <math.h>


struct Parallelepiped_
{
	const double expectedWidth = 5;
	const double expectedHeight = 10;
	const double expectedDepth = 20;
	const double expectedDensity = 2;
	const double expectedVolume = 1000;
	const CParallelepiped parallelepiped;
	Parallelepiped_()
		: parallelepiped(expectedWidth, expectedHeight, expectedDepth, expectedDensity)
	{}
};
BOOST_FIXTURE_TEST_SUITE(parallelepiped, Parallelepiped_)
	//дожно создаться тело
	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&parallelepiped));
	}
	//должна быть ширина и совпасть с ожидаемой
	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetWidth(), expectedWidth);
	}
	//должна быть высота и совпасть с ожидаемой
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetHeight(), expectedHeight);
	}
	//должна быть глубина и совпасть с ожидаемой
	BOOST_AUTO_TEST_CASE(has_a_depth)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetDepth(), expectedDepth);
	}
	//должна быть плотность и совпасть с ожидаемой
	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(parallelepiped).GetDensity(), expectedDensity);
	}
	//должен быть объём и совпасть с ожидаемым
	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(parallelepiped).GetVolume(), expectedVolume, 1e-7);
	}
	//должна быть масса и совпасть с ожидаемой
	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(parallelepiped).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}
	//проверка соответсвия ожидаемой инфы о фигуре с полученной, после инициализации фигуры
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = "Parallelepiped:\n\tdensity = 2\n\tvolume = 1000\n\tmass = 2000\n\twidth = 5\n\theight = 10\n\tdepth = 20\n";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(parallelepiped).ShowInfo(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()
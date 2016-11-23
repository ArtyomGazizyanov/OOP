#include "stdafx.h" 
#define _USE_MATH_DEFINES
#include "../laba4/CSphere.h" 
#include <math.h>

struct Sphere_
{
	const double expectedDensity = 10.8;
	const double expectedRadius = 20.8;
	const double expectedVolume = 37694.55444;
	const CSphere sphere;
	Sphere_()
		: sphere(expectedDensity, expectedRadius)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Sphere, Sphere_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&sphere));
	}

	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(sphere.GetRadius(), expectedRadius);
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(sphere).GetDensity(), expectedDensity);
	}
	
	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sphere).GetVolume(), expectedVolume, 1e-7);
	}
	
	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sphere).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = "Sphere:\n\tdensity = 10.8\n\tvolume = 37694.55444\n\tmass = 407101.1879\n\tradius = 20.8\n";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(sphere).ShowInfo(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()

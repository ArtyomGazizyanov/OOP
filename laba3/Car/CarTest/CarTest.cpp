#include "stdafx.h"
#include "../Car/Car.h" 
#include "../Car/CarController.h"

struct CarFixture
{
	CCar myCar;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_CASE(is_engine_turned_off_ath_the_begining)
	{
		BOOST_CHECK(!myCar.IsEngineOn());
	}

	BOOST_AUTO_TEST_SUITE(if_engine_turned_off)

		BOOST_AUTO_TEST_CASE(should_be_neutral_gear_by_default)
		{
			BOOST_CHECK(myCar.GetCurrentGear() == 0);
		}

		BOOST_AUTO_TEST_CASE(ability_to_set_neutral_gear)
		{
			BOOST_CHECK(myCar.SetGear(0));
		}
		 		
		BOOST_AUTO_TEST_CASE(no_speed_by_default)
		{
			BOOST_CHECK(myCar.GetCurrnetSpeed() == 0);
		} 

		BOOST_AUTO_TEST_CASE(ability_to_turn_on_engine)
		{
			BOOST_CHECK(myCar.TurnOnEngine());
		} 

		BOOST_AUTO_TEST_SUITE_END()

		struct when_turned_on_ : CarFixture
		{
			when_turned_on_()
			{
				myCar.TurnOnEngine();
			}
		};

		BOOST_FIXTURE_TEST_SUITE(if_engine_turned_on, when_turned_on_)

			BOOST_AUTO_TEST_CASE(engine_cant_be_turned_on)
			{
				BOOST_CHECK(!myCar.TurnOnEngine());
			}
		 
			BOOST_AUTO_TEST_SUITE(set_gear_function)

				BOOST_AUTO_TEST_CASE(can_set_reverse_gear)
				{
					BOOST_CHECK(myCar.SetGear(-1));
				}

				BOOST_AUTO_TEST_CASE(can_set_first_gear)
				{
					BOOST_CHECK(myCar.SetGear(1));
				}

				BOOST_AUTO_TEST_CASE(cant_set_gear_out_of_range)
				{
					BOOST_CHECK(!myCar.SetGear(10));
				}

				BOOST_AUTO_TEST_CASE(cant_set_gear_without_required_speed)
				{
					BOOST_CHECK(!myCar.SetGear(3));
				}

				BOOST_AUTO_TEST_CASE(can_set_reverse_gear_from_neutral_gear_and_none_speed)
				{
					BOOST_CHECK(myCar.SetGear(-1));
				}

				BOOST_AUTO_TEST_CASE(can_set_reverse_gear_from_first_gear_and_none_speed)
				{
					myCar.SetGear(1);
					myCar.SetSpeed(0);
					BOOST_CHECK(myCar.SetGear(-1));
				}

				BOOST_AUTO_TEST_CASE(cant_set_reverse_gear_from_other_gears)
				{
					myCar.SetGear(1);
					myCar.SetSpeed(30);
					myCar.SetGear(2);
					BOOST_CHECK(!myCar.SetGear(-1));
				}

				BOOST_AUTO_TEST_CASE(can_set_first_gear_from_reverse_gear_and_none_speed)
				{
					myCar.SetGear(-1);
					myCar.SetSpeed(0);
					BOOST_CHECK(myCar.SetGear(1));
				}

				BOOST_AUTO_TEST_CASE(cant_set_first_gear_after_reverse_gear_and_non_none_speed)
				{
					myCar.SetGear(-1);
					myCar.SetSpeed(10);
					myCar.SetGear(0);
					BOOST_CHECK(!myCar.SetGear(1));
				}

				BOOST_AUTO_TEST_CASE(can_set_first_gear_after_reverse_gear_and_none_speed)
				{
					myCar.SetGear(-1);
					myCar.SetSpeed(10);
					myCar.SetGear(0);
					myCar.SetSpeed(0);
					BOOST_CHECK(myCar.SetGear(1));
				}

			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(set_speed_function)

			BOOST_AUTO_TEST_CASE(can_set_allowed_speed_for_gear)
			{
				myCar.SetGear(1);
				BOOST_CHECK(myCar.SetSpeed(10));
			}

			BOOST_AUTO_TEST_CASE(cant_set_speed_out_of_gear_speed_range)
			{
				myCar.SetGear(1);
				BOOST_CHECK(!myCar.SetSpeed(100));
			}

			BOOST_AUTO_TEST_CASE(cant_change_on_neutral_gear)
			{
				myCar.SetGear(1);
				myCar.SetSpeed(10);
				myCar.SetGear(0);
				BOOST_CHECK(!myCar.SetSpeed(15));
			}

			BOOST_AUTO_TEST_CASE(can_slow_down_at_neutral_gear)
			{
				myCar.SetGear(1);
				myCar.SetSpeed(20);
				myCar.SetGear(0);
				BOOST_CHECK(myCar.SetSpeed(10));
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Turn_off_function)

			BOOST_AUTO_TEST_CASE(engine_can_be_turned_off_at_neutral_gear_and_with_no_speed)
			{
				BOOST_CHECK(myCar.TurnOffEngine());
			}

			BOOST_AUTO_TEST_CASE(engine_cant_be_turned_off_at_neutral_gear_and_with_no_speed)
			{
				myCar.SetGear(1);
				myCar.SetSpeed(20);
				myCar.SetGear(0);
				BOOST_CHECK(!myCar.TurnOffEngine());
			}

			BOOST_AUTO_TEST_CASE(engine_cant_be_turned_off_at_neutral_gear)
			{
				myCar.SetGear(1);
				BOOST_CHECK(!myCar.TurnOffEngine());
			}

		BOOST_AUTO_TEST_SUITE_END()
		
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
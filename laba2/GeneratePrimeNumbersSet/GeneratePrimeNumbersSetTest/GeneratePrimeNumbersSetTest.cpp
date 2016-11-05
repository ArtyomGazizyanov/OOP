#include "stdafx.h"
#include "../GeneratePrimeNumbersSet/GeneratePrimeNumbersSet.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(InitializationOfPrimes_function)
	//создаем пустой вектор
	BOOST_AUTO_TEST_CASE(generate_empty_vector)
	{
		vector<bool> expectedVector{};
		auto result = InitializationOfPrimes(0);

		BOOST_CHECK(result == expectedVector);
	}

	//—оздаем множество простых чисел, наход€щихс€ от 0 до 10
	BOOST_AUTO_TEST_CASE(generate_vector_with_primaries_from_zero_to_ten)
	{
		vector<bool> expectedVector{ 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0 };
		auto result = InitializationOfPrimes(10);

		BOOST_CHECK(result == expectedVector);
	} 
BOOST_AUTO_TEST_SUITE_END()
 
BOOST_AUTO_TEST_SUITE(GeneratePrimeNumberSet_function)

	//должно получитьс€ пустое множество при генерации до 2 и более 10000000 
	BOOST_AUTO_TEST_CASE(generate_empty_set)
	{
		set<int> expectedSet{};
		auto result = GeneratePrimeNumberSet(1);

		BOOST_CHECK(result == expectedSet);
	} 

	//сгенерировать множество если верхн€€ граница равна 3, должно получитс€ {2,3}
	BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_is_3)
	{
		set<int> expectedSet{ 2, 3 };
		auto result = GeneratePrimeNumberSet(3);

		BOOST_CHECK(result == expectedSet);
	}
	//функци€ должна вернуть пустое множество, если верхн€€ граница больще 10000000
	BOOST_AUTO_TEST_CASE(generate_set_more_than_max)
	{
		set<int> expectedSet{};
		auto result = GeneratePrimeNumberSet(1000000010);

		BOOST_CHECK(result == expectedSet);
	}

	//узнаем кол-во сгенерированных простых слов
	BOOST_AUTO_TEST_CASE(generate_set_of_100_primes)
	{ 
		auto expectedSet = 168;
		auto result = GeneratePrimeNumberSet(1000);

		BOOST_CHECK(result.size() == expectedSet);
	}

#ifndef _DEBUG
	//ѕроверка максимального значени€
	BOOST_AUTO_TEST_CASE(generate_max_size_set)
	{
		auto expectedSet = 5761455;
		auto result = GeneratePrimeNumberSet(100000000);

		BOOST_CHECK(result.size() == expectedSet);
	}
#endif


BOOST_AUTO_TEST_SUITE_END()

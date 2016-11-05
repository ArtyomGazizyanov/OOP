#include "stdafx.h"
#include "../GeneratePrimeNumbersSet/GeneratePrimeNumbersSet.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(InitializationOfPrimes_function)
	//������� ������ ������
	BOOST_AUTO_TEST_CASE(generate_empty_vector)
	{
		vector<bool> expectedVector{};
		auto result = InitializationOfPrimes(0);

		BOOST_CHECK(result == expectedVector);
	}

	//������� ��������� ������� �����, ����������� �� 0 �� 10
	BOOST_AUTO_TEST_CASE(generate_vector_with_primaries_from_zero_to_ten)
	{
		vector<bool> expectedVector{ 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0 };
		auto result = InitializationOfPrimes(10);

		BOOST_CHECK(result == expectedVector);
	} 
BOOST_AUTO_TEST_SUITE_END()
 
BOOST_AUTO_TEST_SUITE(GeneratePrimeNumberSet_function)

	//������ ���������� ������ ��������� ��� ��������� �� 2 � ����� 10000000 
	BOOST_AUTO_TEST_CASE(generate_empty_set)
	{
		set<int> expectedSet{};
		auto result = GeneratePrimeNumberSet(1);

		BOOST_CHECK(result == expectedSet);
	} 

	//������������� ��������� ���� ������� ������� ����� 3, ������ ��������� {2,3}
	BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_is_3)
	{
		set<int> expectedSet{ 2, 3 };
		auto result = GeneratePrimeNumberSet(3);

		BOOST_CHECK(result == expectedSet);
	}
	//������� ������ ������� ������ ���������, ���� ������� ������� ������ 10000000
	BOOST_AUTO_TEST_CASE(generate_set_more_than_max)
	{
		set<int> expectedSet{};
		auto result = GeneratePrimeNumberSet(1000000010);

		BOOST_CHECK(result == expectedSet);
	}

	//������ ���-�� ��������������� ������� ����
	BOOST_AUTO_TEST_CASE(generate_set_of_100_primes)
	{ 
		auto expectedSet = 168;
		auto result = GeneratePrimeNumberSet(1000);

		BOOST_CHECK(result.size() == expectedSet);
	}

#ifndef _DEBUG
	//�������� ������������� ��������
	BOOST_AUTO_TEST_CASE(generate_max_size_set)
	{
		auto expectedSet = 5761455;
		auto result = GeneratePrimeNumberSet(100000000);

		BOOST_CHECK(result.size() == expectedSet);
	}
#endif


BOOST_AUTO_TEST_SUITE_END()

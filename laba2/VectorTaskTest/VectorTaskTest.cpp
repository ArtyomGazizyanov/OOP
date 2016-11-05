#include "stdafx.h"
#include "..\VectorTask\VectorTask.h"
#include <math.h>

using namespace std;

bool areVectorsEquals(vector<double> vector1, vector<double> vector2)
{
	if (vector1.size() != vector2.size())
	{
		return false;
	}
	for (unsigned i = 0; i < vector1.size(); ++i)
	{
		if (fabs(vector1[i] - vector2[i]) > 0.00001 * fabs(vector1[i]))
		{
			return false;
		}
	}
	return true;
}
 
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

 //ProcessVector должен вернуть пустой вектор, при передачи ему пусотго вектора
BOOST_AUTO_TEST_CASE(creates_empty_vector_from_empty_vector)
{
	vector<double> emptyVector;
	ProcessVector(emptyVector);
	BOOST_CHECK(emptyVector.empty());
}

//Если передать функции ProcessVector вектор, состоящий из нулей, то функция не должна его изменить
BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_zero_numbers)
{
	vector<double> numbers = { 0, 0, 0 };
	vector<double> copy(numbers);
	ProcessVector(numbers);
	BOOST_CHECK(areVectorsEquals(numbers, copy));
}
 
//Функция ProcessVector не должна изменить нечетные отрицательные елементы вектора, если на четных стоят нули
BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_negative_evens_numbers_and_zero_odds_numbers)
{
	vector<double> numbers = { -1, 0, -2, 0, -3, 0, -79, 0, -69, 0 };
	vector<double> copy(numbers);
	ProcessVector(numbers);
	BOOST_CHECK(areVectorsEquals(numbers, copy));
}
 
//проверка работы функции только с положительными числами.
BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_positive_numbers)
{
	vector<double> numbers = { 1, 2.5, 3, 4.7, 5, 6.9, 7, 8.2, 9, 0 };
	vector<double> numbersRequired = { -46.3, 5, -44.3, 9.4, -42.3, 13.8, -40.3, 16.4, -38.3, 0 };
	ProcessVector(numbers);
	BOOST_CHECK(areVectorsEquals(numbers, numbersRequired));
} 

//проверка полной работоспособности функции.
BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_any_numbers)
{
	vector<double> numbers = { -1, -53.21, 1, 24.112, -213.521, 9842.124 };
	vector<double> numbersRequired = { -9868.236, -106.42, -9866.236, 48.224, -10080.757, 19684.248 };
	ProcessVector(numbers);
	BOOST_CHECK(areVectorsEquals(numbers, numbersRequired));
}

BOOST_AUTO_TEST_SUITE_END()
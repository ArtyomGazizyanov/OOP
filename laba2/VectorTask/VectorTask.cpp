// VectorTask.cpp: определяет точку входа для консольного приложения.
 

#include "VectorTask.h"
#include <vector>
#include <iostream>
#include <string>
#include "Consts.h"
#include <sstream>

double SumAllPositivesNumbers(std::vector<double> const &numbers)
{
	double positiveNumberSum = 0;
	for (double number : numbers)
	{
		positiveNumberSum += (number > 0) ? number : 0;
	}
	return positiveNumberSum;
}

void CalculateEvensElementsWithPositiveSum(std::vector<double> &numbers)
{
	if (numbers.size() > 0)
	{
		double positiveNumberSum = SumAllPositivesNumbers(numbers);
		for (unsigned i = 0; i < numbers.size(); i += 2)
		{
			numbers[i] -= positiveNumberSum;
		}
	}
}

void multiplayOddsEltsByTwo(std::vector<double> &numbers)
{
	for (size_t i = 1; i < numbers.size(); i += 2)
	{
		numbers[i % numbers.size()] *= 2;
	}
}

void ProcessVector(std::vector<double> &numbers)
{
	CalculateEvensElementsWithPositiveSum(numbers);
	multiplayOddsEltsByTwo(numbers);
}
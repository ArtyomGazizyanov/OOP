// GeneratePrimeNumbersSet.cpp: определяет точку входа для консольного приложения.
// 

#include "stdafx.h"
#include "GeneratePrimeNumbersSet.h"

using namespace std;
vector<bool> InitializationOfPrimes(unsigned int upperBound)
{
	std::vector<bool> VectorWithPrimesLocation(upperBound + 1, true);
	if (upperBound >= 2 && upperBound <= 100000001)
	{
		VectorWithPrimesLocation[0] = VectorWithPrimesLocation[1] = false;
		for (unsigned int i = 2; i * i < upperBound; ++i)
		{
			if (VectorWithPrimesLocation[i])
			{
				for (unsigned int j = i * i; j <= upperBound; j += i)
				{
					VectorWithPrimesLocation[j] = false;
				}
			}
		}
	}
	else
	{
		VectorWithPrimesLocation = {};
	}

	return VectorWithPrimesLocation;
}


set<int> GeneratePrimeNumberSet(int upperBound) 
{
	set<int> simpleNumbers;
	set<int> numbers;
	std::set<int> result;

	if (upperBound >= 2 && upperBound < 100000001)
	{
		std::vector<bool> tmpSet = InitializationOfPrimes(upperBound + 1);
		result.insert(2);
		for (int i = 3; i <= upperBound; i += 2)
		{
			if (tmpSet[i])
			{
				result.insert(i);
			}
		}
	}
	else
	{
		result = {};
	}
	return result ;
}

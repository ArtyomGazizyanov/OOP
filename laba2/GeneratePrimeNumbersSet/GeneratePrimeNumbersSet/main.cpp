#include "stdafx.h"
#include "GeneratePrimeNumbersSet.h"

int main()
{
	set<int> set = GeneratePrimeNumberSet(100000000);
	cout << set.size() << endl;
	system("pause");

	return 0;
}
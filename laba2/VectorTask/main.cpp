// main.cpp: определяет точку входа для консольного приложения.
// 

#include "stdafx.h" 
#include "VectorTask.h"

using namespace std;

int main()
{
	std::vector<double> numbersVector;
	string inputString; 
	
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
	copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(numbers)); 

	ProcessVector(numbers); 
	sort(numbers.begin(), numbers.end());

	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));  

	return 0;
}
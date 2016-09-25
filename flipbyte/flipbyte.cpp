// flipbyte.cpp: определяет точку входа для консольного приложения.
 
#include <iostream>
#include <stdlib.h>

using namespace std;

bool IsArgumentsError(int countArguments)
{
	if (countArguments != 2)
	{ 
		return true;
	}	
	return false;
}

bool IsnumberContainsOnlyDegits(string number)
{
	for (unsigned int i = 0; i < number.length(); i++)
	{
		if (!isdigit(number[i]))
		{
			return false;
		}
	}
	return true;
}

bool isNumberValid(int number)
{
	if ((number >= 0) && (number <= 255))
	{		
		return true;
	}	
	return false;
}

unsigned char ReverseByte(unsigned char byte)
{
	byte = (byte & 0b11110000) >> 4 | (byte & 0b00001111) << 4;
	byte = (byte & 0b11001100) >> 2 | (byte & 0b00110011) << 2;
	byte = (byte & 0b10101010) >> 1 | (byte & 0b01010101) << 1;
	return byte;
}

int main(int argc, char* argv[])
{ 
	if (IsArgumentsError(argc))
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: flipbyte.exe <number>" << endl;
	}
	else
	{
		int number = atoi(argv[1]);
		if (IsnumberContainsOnlyDegits(argv[1]))
		{
			if (isNumberValid(number))
			{
				unsigned char byte = number;
				int reverseNumber = (int)ReverseByte(byte);
				cout << reverseNumber << endl;
			}
			else
			{
				cout << "Invalid argument! Number must be from 0 to 255" << endl;
			}
		}
		else
		{
			cout << "Invalid argument! argument contains the letter (s)" << endl;
		}
	}
	return 0;
}
// findtext.cpp: определяет точку входа для консольного приложения.

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void FindMatches(ifstream &file, string searchStr)
{

	int currentLine = 1;
	int countOfMatches = 0;
	bool searchSuccess = false;
	string line;
	while (getline(file, line))
	{
		if (line.find(searchStr) != string::npos)
		{
			searchSuccess = true;
			countOfMatches++;
			cout << countOfMatches << ") number of line: " << currentLine << '\n';
		}
		currentLine++;
	}

	if (!searchSuccess)
	{
		cout << "Text not found! \n";
	}
}

bool IfFileHasErrors(ifstream &file)
{
	if (!file.is_open())
	{
		cout << "Failed to open This file doesn`t exist)\n";
		return false;
	}
	if (!file.good())
	{
		cout << "Error: reading file problem. Found some errors in the file! \n"
			<< "PLease, check file \n";
		return false;
	}
	return true;
}

bool IfStringHasErrors(string searchStr)
{
	if (searchStr.length() == 0)
	{
		cout << "You wrote nothing to search!" << "\n";
		return false;
	}
	return true;
}

bool IfArgumentsHasErrors(int arguments)
{
	if (arguments != 3)
	{
		cout << "Invalid arguments count \n"
			<< "Usage: findtext.exe <file name> <text to search> \n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	if (!IfArgumentsHasErrors(argc))
	{
		return 1;
	}

	ifstream file(argv[1]);
	if (!IfFileHasErrors(file))
	{
		return 1;

	}

	string searchStr = string(argv[2]);
	if (!IfStringHasErrors(searchStr))
	{
		return 1;
	}

	FindMatches(file, searchStr);
	return 0;
}
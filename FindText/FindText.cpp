// findtext.cpp: определяет точку входа для консольного приложения.
//

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	if (argc != 3)
	{
		cout << "Invalid arguments count \n"
			<< "Usage: findtext.exe <file name> <text to search> \n";
		return 1;
	}

	ifstream file(argv[1]);	 
	if (!file.is_open())
	{
		cout << "Failed to open " << argv[1] << " (This file doesn`t exist)\n";
		return 1;
	}
	if (!file.good())
	{
		cout << "Error: reading file problem. Found some errors in the file! \n"
			<< "PLease, check filename" << argv[1] << " \n";
		return 1;
	}

	string searchStr = string(argv[2]);

	if (searchStr.length() == 0)
	{
		cout << "You wrote nothing to search!" << "\n";
		return 1;
	}
	if (searchStr.length() > 255)
	{
		cout << "You string isn`t correct. It`s lenght must be less than 255! \n" 
			 << "Your string has lenght  = " << searchStr.length() << "\n";
		return 1;
	}

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
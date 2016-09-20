#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	if (argc != 1)
	{
		cout << "Invalid arguments count \n"
			<< "Usage: flipbyte.exe <number> \n";
		return 1;
	}
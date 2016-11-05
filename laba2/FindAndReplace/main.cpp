#include "FindAndReplace.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	if (argc != 4)
	{
		cout << "There`s no 4 arguments. Please write correct ammount of arguments." << "\n";
		return 1;
	}

	string subject = argv[1];
	if (subject == "")
	{
		cout << "Subject string is empty" << "\n";
		return 1;
	}
	string search = argv[2]; 
	if (search == "")
	{
		cout << "Search string is empty" << "\n";
		return 1;
	} 
	string replace = argv[3];
	if (replace == "")
	{
		cout << "Replace string is empty" << "\n";
		return 1;
	}

	cout << FindAndReplace(subject, search, replace) << "\n";

	return 0;
}
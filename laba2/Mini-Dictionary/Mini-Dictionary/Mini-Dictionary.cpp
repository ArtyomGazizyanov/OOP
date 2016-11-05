// Mini-Dictionary.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "DictionaryProcessor.h"

using namespace std;

int main()
{	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	map<string, string> dictionary;
	size_t firstDictionarySize = 0;
	size_t lastDictionarySize = 0;

	InitializationDictionary(dictionary);
	firstDictionarySize = dictionary.size();
	ReadLoop(dictionary);

	lastDictionarySize = dictionary.size();
	if (firstDictionarySize != lastDictionarySize)
	{
		DoSaveChange(dictionary);
	}
	else
	{
		cout << "До свидания!" << endl;
	}
    return 0;
}


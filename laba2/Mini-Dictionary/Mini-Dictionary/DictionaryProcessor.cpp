
#include "stdafx.h"
#include "DictionaryProcessor.h"

using namespace std;

string FindAndReplace(string const& subject, string const& search, string  const& replace)
{
	size_t pos = 0;
	string resSubject;
	resSubject = subject;
	pos = resSubject.find(search, pos);
	while (pos != string::npos && search != "")
	{
		resSubject.replace(pos, search.length(), replace);
		pos = pos + replace.length();
		pos = resSubject.find(search, pos - 1);
	}
	return resSubject;
}

int CountWordsInALine(string line)
{
	int i = 0;
	int CountOfWords = 0;
	bool isWord = false;
	while (line[i] == ' ' && line[i] != '\0')
	{
		i++;
	}
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && !isWord)
		{
			isWord = true;
			CountOfWords++;
		}
		else
			if (line[i] == ' ')
			{
				isWord = false;
			}
		i++;
	}
	return CountOfWords;
}

string ReadKeyWord(stringstream &lineStream, int &wordsCounter)
{
	string word;
	string key;
	lineStream >> word;
	while (word != SEPARATE_SYMBOL_BETWEEN_WORDS)
	{
		key += word;
		lineStream >> word;
		if (word != SEPARATE_SYMBOL_BETWEEN_WORDS)
		{
			key += SPACE;
		}
		wordsCounter++;
	}

	return key;
}

string ReadTranslation(stringstream &lineStream, int &wordsCounter, int const& wordsInLine)
{
	string translation = "";
	string word = "";
	while (lineStream >> word)
	{
		wordsCounter++;
		if (word != SEPARATE_SYMBOL_BETWEEN_WORDS)
		{
			if (wordsCounter < wordsInLine - 1)
			{
				translation += word + SPACE;
			}
			else
			{
				translation += word;
			}
		}
		else
		{
			translation += ", ";
		}
	}

	return translation;
}

void InitializationDictionary(map<string, string> &dictionary)
{
	ifstream file("WordsDatabase.txt");
	if (file.is_open())
	{
		string key = "";
		string translation = "";
		while (file)
		{
			string line;
			string word;
			stringstream lineStream;
			int countOfWords;
			while (getline(file, line))
			{
				countOfWords = CountWordsInALine(line);
				if (countOfWords >= 3)
				{
					int currentWord = 0;
					lineStream.clear();
					lineStream << line << ' ';
					key = ReadKeyWord(lineStream, currentWord);
					translation = ReadTranslation(lineStream, currentWord, countOfWords);
					dictionary.emplace(key, translation);
				}
			}
		}
	}
}

string GetTranslationAnswer(map<string, string> &dictionary, string newWord, string translationOfNewWord)
{
	string answer = "";
	if (translationOfNewWord.length() == 0)
	{
		answer = "Слово '" + newWord + "' проигнорировано.";
	}
	else
	{
		dictionary.emplace(newWord, translationOfNewWord);
		answer = "Слово '" + newWord + "' сохранено в словаре как '" + translationOfNewWord + "'.";
	}

	return answer;
}

void SaveChangedDictionary(map<string, string> dictionary)
{
	ofstream  fileOut;
	fileOut.open("WordsDatabase.txt");
	fileOut.clear();
	string translationString = "";

	for (auto wordCombination = dictionary.begin(); wordCombination != dictionary.end(); wordCombination++)
	{
		translationString = wordCombination->second;
		translationString = FindAndReplace(translationString, ",", " -");
		fileOut << wordCombination->first << " - " << translationString << endl;
	}
	fileOut.close();
}

string BuildTranslatingWord(string inputString)
{
	string inputWord = "";
	stringstream stringStream;
	int countOfWords = CountWordsInALine(inputString);
	int currentWord = 0;
	stringStream << inputString;
	string translatingPhrase;
	if (countOfWords > 1)
	{
		while (stringStream >> inputWord)
		{
			currentWord++;
			if (currentWord != countOfWords)
			{
				translatingPhrase += inputWord + " ";
			}
			else
			{
				translatingPhrase += inputWord;
			}
		}
	}
	else
	{
		translatingPhrase = inputString;
	}

	transform(translatingPhrase.begin(), translatingPhrase.end(), translatingPhrase.begin(), tolower);

	return translatingPhrase;
}

string GetTranslatingWord()
{
	string inputString = "";
	string translatingPhrase = "";
	string inputWord = "";
	stringstream stringStream;

	getline(cin, inputString);
	translatingPhrase = BuildTranslatingWord(inputString);
	return translatingPhrase;
}

void ReadLoop(map<string, string> &dictionary)
{
	string inputWord = "";
	while (inputWord != "...")
	{
		cout << "Введите слово" << endl;
		inputWord = GetTranslatingWord();
		if (inputWord != "...")
		{
			if (dictionary.count(inputWord))
			{
				cout << inputWord << ": " << dictionary[inputWord] << endl;
			}
			else
			{
				string inputAnswer;
				cout << "Неизвестное слово '" << inputWord << "'.Введите перевод или пустую строку для отказа." << endl;
				getline(cin, inputAnswer);
				if (inputAnswer.size() != 0)
				{
					transform(inputAnswer.begin(), inputAnswer.end(), inputAnswer.begin(), tolower);
					cout << GetTranslationAnswer(dictionary, inputWord, inputAnswer) << endl;
				}
			}
		}
	}
}

void DoSaveChange(map<string, string> &dictionary)
{
	string inputWord;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;
	cin >> inputWord;
	if (inputWord == "Y" || inputWord == "y")
	{
		SaveChangedDictionary(dictionary);
	}
} 

void StartDictionary()
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
}

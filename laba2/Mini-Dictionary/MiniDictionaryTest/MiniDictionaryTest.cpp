#include "stdafx.h"
#include "../Mini-Dictionary/DictionaryProcessor.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Dictionary_function)
	//проверем инициализацию словаря
	BOOST_AUTO_TEST_CASE(check_initialization_of_dicionary)
	{ 
		map<string, string> dictionary;
		InitializationDictionary(dictionary);

		string expectedTranslation = "удар";
		string result = dictionary["hook"]; 

		BOOST_CHECK(expectedTranslation == result);
	}
	//проверяем может ли функция считать из файла словосочетания
	BOOST_AUTO_TEST_CASE(check_dicionary_with_two_or_more_words)
	{ 
		map<string, string> dictionary;
		InitializationDictionary(dictionary);

		string expectedTranslation = "красная площадь";
		string result = dictionary["the red square"];

		BOOST_CHECK(expectedTranslation == result);
	}
	//должны получить перевод слова из словаря
	BOOST_AUTO_TEST_CASE(check_getting_translating_word)
	{ 

		map<string, string> dictionary;
		InitializationDictionary(dictionary);
		string inputString = "My moTher";
		string expectedTranslation = "my mother";
		string result = BuildTranslatingWord(inputString);


		BOOST_CHECK(expectedTranslation == result);
	}
	//проверка добавления нового слова в map 
	BOOST_AUTO_TEST_CASE(check_adding_translation)
	{ 
		map<string, string> dictionary;
		InitializationDictionary(dictionary);
		string word = "chicken";
		string translationOfWord = "кура";
		string expectedTranslation = "Слово '" + word + "' сохранено в словаре как '" + translationOfWord + "'.";
		string result = GetTranslationAnswer(dictionary, word, translationOfWord); 


		BOOST_CHECK(expectedTranslation == result);
	}
	//проверка сохранения новго слова в map с последующим сохранением в файл, и выводом проверки
	//должны получить перевод нововведенного слова
	BOOST_AUTO_TEST_CASE(check_saving_new_world)
	{
		map<string, string> dictionary;
		InitializationDictionary(dictionary);
		string word = "chicken";
		string translationOfWord = "кура";
		string expectedTranslation = "кура";
		GetTranslationAnswer(dictionary, word, translationOfWord);

		SaveChangedDictionary(dictionary);
		string result = dictionary["chicken"];
		BOOST_CHECK(expectedTranslation == result);
		dictionary["chicken"].clear();
	}
BOOST_AUTO_TEST_SUITE_END()
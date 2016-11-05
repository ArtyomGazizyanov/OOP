#pragma once

#include "stdafx.h"

using namespace std;

void StartDictionary();
string FindAndReplace(string const& subject, string const& search, string  const& replace);
void InitializationDictionary(map<string, string> &dictionary);
void ReadLoop(map<string, string> &dictionary);
void DoSaveChange(map<string, string> &dictionary);
string GetTranslatingWord();
string BuildTranslatingWord(string inputString);
string GetTranslationAnswer(map<string, string> &dictionary, string newWord, string translationOfNewWord);
void SaveChangedDictionary(map<string, string> dictionary);
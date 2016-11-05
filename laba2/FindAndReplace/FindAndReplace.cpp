// FindAndReplace.cpp: определяет точку входа для консольного приложения.
//
#include "FindAndReplace.h"

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

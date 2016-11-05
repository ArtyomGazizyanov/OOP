// FindAndReplaceTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../FindAndReplace/FindAndReplace.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FindAndReplace_function)
	BOOST_AUTO_TEST_CASE(check_empty_subject)
	{
		string subject = "";
		string search = "FindMe";
		string replace = "InsertMe";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "");
	}
	BOOST_AUTO_TEST_CASE(check_empty_search)
	{
		string subject = "GivenSubject";
		string search = "";
		string replace = "InsertMe";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "GivenSubject");
	}
	BOOST_AUTO_TEST_CASE(check_empty_replace)
	{
		string subject = "Subject";
		string search = "Sub";
		string replace = "";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "ject");
	}
	BOOST_AUTO_TEST_CASE(check_standart_data)
	{
		string subject = "GivenSubject";
		string search = "Sub";
		string replace = "ject";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "Givenjectject");
	}
	BOOST_AUTO_TEST_CASE(check_double_replace)
	{
		string subject = "subject";
		string search = "sub";
		string replace = "subsub";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "subsubject");
	}
	BOOST_AUTO_TEST_CASE(check_double_search)
	{
		string subject = "mama subject";
		string search = "mama";
		string replace = "this is";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "this is subject");
	}

BOOST_AUTO_TEST_SUITE_END()
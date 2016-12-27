// StringListTests.cpp: определяет точку входа для консольного приложения.
//

//ассерт ++
//в общую функцию вынести инпут
//тесты и в той тоже
#include "stdafx.h"
#include <iostream>
#include "../StringList/StringList.h"

void VerifyList(CStringList & list, std::vector<string> & expectedElements)
{
	size_t counter = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedElements[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_SUITE(StringList_tests)

	struct StringListFix
	{
		vector<string> bigList = {"Mama", "told", "us", "we", "are", "young"};
	};
 

	BOOST_AUTO_TEST_CASE(check_first_size)
	{
		BOOST_CHECK_EQUAL(CStringList().GetSize(), 0);
	}

	BOOST_AUTO_TEST_CASE(check_is_empty)
	{
		BOOST_CHECK_EQUAL(CStringList().IsEmpty(), true);
	}

	BOOST_AUTO_TEST_CASE(input_into_the_front_of_list)
	{
		CStringList mylist; 
		mylist.PushFront("Hello");
		BOOST_CHECK_EQUAL(mylist.GetSize(), 1);
	}

	BOOST_AUTO_TEST_CASE(input_into_the_back_of_list)
	{
		CStringList mylist;
		mylist.PushBack("Hello");
		BOOST_CHECK_EQUAL(mylist.GetSize(), 1);
	}

	BOOST_AUTO_TEST_CASE(can_clear_list)
	{
		CStringList mylist;
		mylist.PushBack("Hello");
		std::cout << "FIRST INSERTED!!!!!!!!" << endl;
		mylist.PushBack("world");
		mylist.Clear();
		BOOST_CHECK_EQUAL(mylist.GetSize(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_insert_element_at_iterator_pos)
	{
		CStringList mylist;

		mylist.Insert(mylist.begin(), "11");
		BOOST_CHECK_EQUAL(*mylist.begin(), "11");

		auto it = ++mylist.begin();
		mylist.Insert(it, "20");
		BOOST_CHECK_EQUAL(*++mylist.begin(), "20");

		mylist.Insert(mylist.end(), "30");

		std::vector<std::string> expectedStrings = { "11" , "20" , "30" };
		size_t i = 0;
		for (auto str : mylist)
		{
			BOOST_CHECK_EQUAL(str, expectedStrings[i]);
			i++;
		}
	}

	BOOST_AUTO_TEST_CASE(check_isnert_into_full_list)
	{
		StringListFix vector;
		CStringList CStringListVector;
		for (size_t i = 0; i < vector.bigList.size(); ++i)
		{
			CStringListVector.PushBack(vector.bigList[i]);
		}

		CStringListVector.Insert(CStringListVector.end(), "30");
		StringListFix expectedList;
		expectedList.bigList.push_back("30");
		VerifyList(CStringListVector, expectedList.bigList);
	}

	BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_pos)
	{
		StringListFix vector;
		CStringList CStringListVector;
		for (size_t i = 0; i < vector.bigList.size(); ++i)
		{
			CStringListVector.PushBack(vector.bigList[i]);
		}

		auto it = ++CStringListVector.begin();
		BOOST_CHECK_EQUAL(*it, vector.bigList[1]);
		CStringListVector.Erase(it);
		BOOST_CHECK_EQUAL(*++CStringListVector.begin(), vector.bigList[2]);

		CStringListVector.Erase(CStringListVector.begin());
		BOOST_CHECK_EQUAL(*CStringListVector.begin(), vector.bigList[2]);

		CStringListVector.Erase(CStringListVector.begin());
		BOOST_CHECK(!CStringListVector.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(can_get_access_to_elements_from_range_based_for)
	{
		StringListFix expectedVector;
		CStringList CStringListVector;
		for (size_t i = 0; i < expectedVector.bigList.size(); ++i)
		{
			CStringListVector.PushBack(expectedVector.bigList[i]);
		}

		size_t counter = 0;
		for (auto str : CStringListVector)
		{
			BOOST_CHECK_EQUAL(str, expectedVector.bigList[counter]);
			counter++;
		}
	}

	BOOST_AUTO_TEST_CASE(have_reverse_iterators_and_const_revers_iterators_at_begin_and_end_of_string_list)
	{
		StringListFix expectedVector;
		CStringList CStringListVector;
		for (size_t i = 0; i < expectedVector.bigList.size(); ++i)
		{
			CStringListVector.PushBack(expectedVector.bigList[i]);
		}
		size_t counter = expectedVector.bigList.size() - 1;
		for (auto it = CStringListVector.rbegin(); it != CStringListVector.rend(); ++it)
		{
			BOOST_CHECK_EQUAL(*it, expectedVector.bigList[counter]);
			counter--;
		}
	}
	
	BOOST_AUTO_TEST_CASE(cant_errase_empty_list)
	{
		CStringList CStringListVector;
		BOOST_REQUIRE_THROW(CStringListVector.Erase(CStringListVector.begin()), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(have_copy_constructor)
	{
		StringListFix expectedVector;
		CStringList CStringListVector;
		for (size_t i = 0; i < expectedVector.bigList.size(); ++i)
		{
			CStringListVector.PushBack(expectedVector.bigList[i]);
		}
		CStringList copiedList(CStringListVector);
		VerifyList(CStringListVector, expectedVector.bigList);
		VerifyList(copiedList, expectedVector.bigList);
	}

BOOST_AUTO_TEST_SUITE_END()

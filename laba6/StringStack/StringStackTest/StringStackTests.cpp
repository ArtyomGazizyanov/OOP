#include "stdafx.h"
#include "../CStringStack.h"


BOOST_AUTO_TEST_CASE(can_assign_stringstack)
{
	CStringStack stack; 
	BOOST_CHECK_EQUAL(stack.GetSize(), 0); 
}

BOOST_AUTO_TEST_CASE(can_push_new_element_into_stack)
{ 
	CStringStack stack;
	string newString = "Hello world";
	stack.push(newString);
	BOOST_CHECK_EQUAL(stack.GetSize(), 1); 
} 

BOOST_AUTO_TEST_CASE(can_get_top_element_from_stack)
{
	CStringStack stack;
	string newString = "Hello world";
	stack.push(newString);
	BOOST_CHECK_EQUAL(stack.top(), newString);
}
//
//BOOST_AUTO_TEST_CASE(can_get_pop_element_from_stack)
//{
//	CStringStack stack;
//	string newString1 = "Hello world";
//	string newString2 = "My mother";
//	stack.push(newString1); 
//	stack.push(newString2);
//
//	BOOST_CHECK_EQUAL(stack.pop(), newString2);
//	BOOST_CHECK_EQUAL(stack.pop(), newString1);
//
//	BOOST_CHECK_EQUAL(stack.GetSize(), 0);
//} 
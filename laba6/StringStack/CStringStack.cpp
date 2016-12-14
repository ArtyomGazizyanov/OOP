#include "stdafx.h"
#include "CStringStack.h"
#include <stack>
#include<iostream>
 
CStringStack::~CStringStack()
{
	cout << "Destruct" << endl;
	while (m_top->prevElement != nullptr)
	{
		auto tempElement = m_top;
		delete m_top;
		m_top = tempElement->prevElement;
	}
}

CStringStack::CStringStack()
{
	m_top = nullptr;
	m_stackSize = 0;
}


void CStringStack::push(string newString)
{ 
	StackStruct *newElement = new StackStruct;
	newElement->value = newString;
	newElement->prevElement = m_top;
	m_top = newElement;
	m_stackSize++;
}

string CStringStack::pop()
{
	if (m_stackSize > 0)
	{
		StackStruct returnElement = *m_top;
		m_top = returnElement.prevElement;
		m_stackSize--;
		return returnElement.value;
	}
	else
	{
		throw "Stack is empty";
	}
}


string CStringStack::top()
{ 
	if (m_stackSize > 0)
	{
		return m_top->value;
	}
	else
	{ 
		throw "Stack is empty";
	} 
}


int CStringStack::GetSize()
{
	return m_stackSize;
}
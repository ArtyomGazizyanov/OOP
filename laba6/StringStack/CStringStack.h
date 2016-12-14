#pragma once
#include <string>

using namespace std;

struct StackStruct
{
	string value;
	StackStruct* prevElement;
};

class CStringStack 
{
public:
	CStringStack();

	~CStringStack();
	string pop();
	void push(string newElement);
	string top();
	int GetSize();

private:
	StackStruct *m_top;
	int m_stackSize;
};
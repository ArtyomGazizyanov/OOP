#pragma once
#include "stdafx.h"
#include "ListNode.h"
#include "StringListIterator.h"

using namespace std;

class CStringList
{
public:
	friend class ListNode;
	friend class CListIterator<string>;

	CStringList() = default;
	CStringList(CStringList & list);
	~CStringList();

	size_t GetSize();
	bool IsEmpty(); // const?

	void PushBack(const string & data);
	void PushFront(const string & data);
	void Clear();

	void CStringList::Insert(const CListIterator<string> & it, string data);
	void CStringList::Erase(const CListIterator<string> & it);

	string & GetLastElement(); // const?
	const string & GetLastElement() const;

	string & GetFirstElement(); // const?
	const string & GetFirstElement() const;


	CListIterator<string> begin();
	CListIterator<string> end();
	
	const CListIterator<string> cbegin() const;
	const CListIterator<string> cend() const;
	
	CListIterator<string> rbegin();
	CListIterator<string> rend();

	const CListIterator<string> crbegin() const;
	const CListIterator<string> crend() const;

private:
	unique_ptr<ListNode> CStringList::InsertOnTheEdge(const string & data, ListNode * prev, std::unique_ptr<ListNode> && next);
	size_t m_size = 0;
	std::unique_ptr<ListNode> m_firstNode = nullptr;
	ListNode * m_lastNode = nullptr;

};
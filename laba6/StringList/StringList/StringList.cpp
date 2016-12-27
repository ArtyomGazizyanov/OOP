#include "stdafx.h"
#include <iostream>
#include "StringList.h"

CStringList::CStringList(CStringList & list)
{
	CStringList tmp;
	for (auto const& elem : list)
	{
		tmp.PushBack(elem);
	}
	std::swap(m_firstNode, tmp.m_firstNode);
	std::swap(m_lastNode, tmp.m_lastNode);
	m_size = tmp.m_size;
}

CStringList::~CStringList()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
	}
	m_firstNode = nullptr;
	m_size = 0;
}

size_t CStringList::GetSize()
{
	return m_size;
}

bool CStringList::IsEmpty()
{
	return m_size == 0u;
}

void CStringList::PushBack(const string & data)
{
	try
	{
		
		auto newNode = std::make_unique<ListNode>(data, m_lastNode, nullptr);
		ListNode *newLastNode = newNode.get();
		if (m_lastNode)
		{
			m_lastNode->next = std::move(newNode);
		}
		else
		{
			m_firstNode = std::move(newNode);
		}
				
		m_lastNode = newLastNode;
		m_lastNode->next = nullptr;

		++m_size;
	}
	catch (...)
	{
		throw;
	}
}

void CStringList::PushFront(const string & data)
{
	try
	{  		
		auto newNode = InsertOnTheEdge(data, nullptr, std::move(m_firstNode));
		if (!newNode->next)
		{
			m_lastNode = newNode.get();
		}
		m_firstNode = std::move(newNode);
		m_firstNode->prev = nullptr; 

		m_size++;

	}
	catch (...)
	{
		throw;
	}	
}

unique_ptr<ListNode> CStringList::InsertOnTheEdge(const string & data, ListNode * prev, std::unique_ptr<ListNode> && next)
{
	
	try
	{
		auto newNode = std::make_unique<ListNode>(data, prev, std::move(next));
		
		if (newNode->prev)
		{ 
			newNode->prev->next = std::move(newNode);
		}
		else if (newNode->next)
		{
	
			newNode->next->prev = newNode.get();
		}
		return newNode;
	}
	catch (...)
	{
		throw;
	}
}



void CStringList::Clear()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
	}
	m_firstNode = nullptr;
	m_size = 0;
}


void CStringList::Insert(const CListIterator<string> & it, string data)
{
	if (it == begin())
	{
		PushFront(data);
	}
	else if (it == end())
	{
		PushBack(data);
	}
	else
	{
		try
		{
			auto node = std::make_unique<ListNode>(data, it->prev, std::move(it->prev->next));
			it->prev = std::move(node.get());
			node->prev->next = std::move(node);
		}
		catch (...)
		{
			throw;
		}
	}
}


void CStringList::Erase(const CListIterator<string> & it)
{
	if (m_size == 0)
	{
		throw std::out_of_range("List is empty");
	}

	if (m_size == 1)
	{
		Clear();
		return;
	}

	if (it == begin())
	{
		it->next->prev = nullptr;
		m_firstNode = move(it->next);
	}
	else if (it->data == GetLastElement()) 
	{
		it->prev->next = nullptr;
		m_lastNode = std::move(it->prev);
	}
	else
	{
		it->next->prev = std::move(it->prev);
		it->prev->next = std::move(it->next);
	}

	if (m_size > 0)
	{
		m_size--;
	}
}

string &CStringList::GetFirstElement()
{
	if (m_firstNode != nullptr)
	{
		return m_firstNode->data;
	}
	else
	{
		throw std::runtime_error("List hasn`t got first element");
	}
}

const string & CStringList::GetFirstElement() const 
{
	//assert(m_firstNode); // runtime_error
	if (m_firstNode != nullptr)
	{
		return m_firstNode->data;
	}
	else
	{
		throw std::runtime_error("List hasn`t got first element");
	}
	//return m_firstNode->data;
}

string &CStringList::GetLastElement()
{
	if (m_lastNode != nullptr)
	{
		return m_lastNode->data;
	}
	else
	{
		throw std::runtime_error("List hasn`t got last element");
	}
}

const string & CStringList::GetLastElement() const
{ 
	if (m_lastNode != nullptr)
	{
		return m_lastNode->data;
	}
	else
	{
		throw std::runtime_error("List hasn`t got last element");
	}
}

CListIterator<string> CStringList::begin()
{
	return CListIterator<string>(m_firstNode.get(), false);
}

CListIterator<string> CStringList::end()
{
	return CListIterator<string>(m_lastNode->next.get(), false);
}

CListIterator<string> CStringList::rbegin()
{
	return CListIterator<string>(m_lastNode, true);
}

CListIterator<string> CStringList::rend()
{
	return CListIterator<string>(m_firstNode->prev, true);
}

const CListIterator<string> CStringList::cbegin() const
{
	return CListIterator<string>(m_firstNode.get(), false);
}

const CListIterator<string> CStringList::cend() const
{
	return CListIterator<string>(m_lastNode->next.get(), false);
}

const CListIterator<string> CStringList::crbegin() const
{
	return CListIterator<string>(m_lastNode, true);
}

const CListIterator<string> CStringList::crend() const
{
	return CListIterator<string>(m_firstNode->prev, true);
}

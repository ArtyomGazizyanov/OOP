#pragma once
#include "stdafx.h" 
#include "ListNode.h"

template<typename ValueType> 
class CListIterator : public std::iterator <std::input_iterator_tag, ValueType>
{
public:
	CListIterator(ListNode* value, bool isReverse)
		: m_node(value)
		, m_isReverse(isReverse)
	{
	}

	friend class CStringList;

	bool operator!=(CListIterator const& another) const
	{
		return m_node != another.m_node;
	}

	bool operator==(CListIterator const& another) const
	{
		return m_node == another.m_node;
	}

	ValueType & operator*() const
	{
		return m_node->data;
	}

	CListIterator& operator++()
	{
		if (m_isReverse)
		{
			m_node = m_node->prev;
		}
		else
		{
			m_node = m_node->next.get();
		}
		return *this;
	}
	CListIterator& operator--()
	{
		if (m_isReverse)
		{
			m_node = m_node->next.get();
		}
		else
		{
			m_node = m_node->prev;
		}
		return *this;
	} 

private:
	ListNode* operator->()const
	{
		return m_node;
	}

	ListNode* m_node = nullptr;
	bool m_isReverse = false;
};

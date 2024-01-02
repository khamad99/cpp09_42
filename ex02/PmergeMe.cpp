/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:42:48 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 09:05:09 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

pmergeMe::pmergeMe(std::list<int> & input_list) : 
_input(input_list),
_timeList(0),
_timeSet(0) 
{
	return ;
}

pmergeMe::~pmergeMe()
{
	return ;
}

pmergeMe::pmergeMe(const pmergeMe & src)
{
	*this = src;
	return ;
}

pmergeMe & pmergeMe::operator=(const pmergeMe & rhs)
{
	if (this != &rhs)
	{
		this->_l = rhs._l;
		this->_s = rhs._s;
		this->_timeList = rhs._timeList;
		this->_timeSet = rhs._timeSet;
	}
	return (*this);
}

static void mergeList(std::list<int> & lift, std::list<int> & right, std::list<int> & list)
{
	int leftLen = lift.size();
	int rightLen = right.size();
	int l = 0;
	int r = 0;

	while (l < leftLen && r < rightLen)
	{
		if (lift.front() < right.front())
		{
			list.push_back(lift.front());
			lift.pop_front();
			l++;
		}
		else
		{
			list.push_back(right.front());
			right.pop_front();
			r++;
		}
	}
	while (l < leftLen)
	{
		list.push_back(lift.front());
		lift.pop_front();
		l++;
	}
	while (r < rightLen)
	{
		list.push_back(right.front());
		right.pop_front();
		r++;
	}
}

static void margeSortList(std::list<int> & l)
{
	int len = l.size();
	if (len <= 1)
		return ;
	int mid = len / 2;
	std::list<int> left;
	std::list<int> right;
	std::list<int>::iterator it = l.begin();
	for (int i = 0; i < mid; i++)
	{
		left.push_back(*it++);
		l.pop_front();
	}
	for (int i = mid; i < len; i++)
	{
		right.push_back(*it++);
		l.pop_front();
	}
	margeSortList(left);
	margeSortList(right);
	mergeList(left, right, l);

}

static void mergeSet(std::deque<int> & lift, std::deque<int> & right, std::deque<int> & set)
{
	int leftLen = lift.size();
	int rightLen = right.size();
	int l = 0;
	int r = 0;

	while (l < leftLen && r < rightLen)
	{
		if (*lift.begin() < *right.begin())
		{
			set.push_back(*lift.begin());
			lift.erase(lift.begin());
			l++;
		}
		else
		{
			set.push_back(*right.begin());
			right.erase(right.begin());
			r++;
		}
	}
	while (l < leftLen)
	{
		set.push_back(*lift.begin());
		lift.erase(lift.begin());
		l++;
	}
	while (r < rightLen)
	{
		set.push_back(*right.begin());
		right.erase(right.begin());
		r++;
	}
}

static void margeSortSet(std::deque<int> & s)
{
	int len = s.size();
	if (len <= 1)
		return ;
	int mid = len / 2;
	std::deque<int> left;
	std::deque<int> right;
	std::deque<int>::iterator it = s.begin();
	for (int i = 0; i < mid; i++)
	{
		left.push_back(*it++);
		s.pop_front();
	}
	for (int i = mid; i < len; i++)
	{
		right.push_back(*it++);
		s.pop_front();
	}
	margeSortSet(left);
	margeSortSet(right);
	mergeSet(left, right, s);

}

void fillList(std::list<int> & input, std::list<int> & l)
{
	std::list<int>::iterator it = input.begin();
	for (size_t i = 0; i < input.size(); i++)
	{
		l.push_back(*it);
		it++;
	}
}

void fillDeque(std::list<int> & input, std::deque<int> & s)
{
	std::list<int>::iterator it = input.begin();
	for (size_t i = 0; i < input.size(); i++)
	{
		s.push_back(*it);
		it++;
	}
}

void		pmergeMe::margeSort()
{
	clock_t start = clock();
	fillList(this->_input, this->_l);
	margeSortList(this->_l);
	clock_t end = clock();
	this->_timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	fillDeque(this->_input, this->_s);
	margeSortSet(this->_s);
	end = clock();
	this->_timeSet = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void		pmergeMe::print()
{
	std::cout << "Before: " ; 
	for (std::list<int>::iterator it = this->_input.begin(); it != this->_input.end(); it++)
	{
		std::cout << *it;
		if (it != this->_input.end())
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "After: ";
	std::deque<int>::iterator it = this->_s.begin();
	for (size_t i = 0; i < this->_s.size(); i++)
	{
		std::cout << *it;
		if (i < this->_s.size() - 1)
			std::cout << " ";
		it++;
	}
	std::cout << std::endl;
	std::list<int>::iterator it2 = this->_l.begin();
	for (size_t i = 0; i < this->_l.size(); i++)
	{
		std::cout << *it2;
		if (i < this->_l.size() - 1)
			std::cout << " ";
		it2++;
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << this->_l.size()
	<< " elements with std::list : " << std::fixed << std::setprecision(6)
	<< this->_timeList << " us" << std::endl;

	std::cout << "Time to process a range of " << this->_s.size()
	<< " elements with std::deque : " << std::fixed << std::setprecision(6)
	<< this->_timeSet << " us" << std::endl;
}
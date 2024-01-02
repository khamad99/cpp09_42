/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:42:48 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 22:55:30 by kalshaer         ###   ########.fr       */
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

void mergeSet(std::multiset<int> & lift, std::multiset<int> & right, std::multiset<int> & set)
{
    std::multiset<int>::iterator leftIt = lift.begin();
    std::multiset<int>::iterator rightIt = right.begin();

    while (leftIt != lift.end() && rightIt != right.end())
    {
        if (*leftIt < *rightIt)
        {
            set.insert(*leftIt);
            leftIt++;
        }
        else
        {
            set.insert(*rightIt);
            rightIt++;
        }
    }

    while (leftIt != lift.end())
    {
        set.insert(*leftIt);
        leftIt++;
    }

    while (rightIt != right.end())
    {
        set.insert(*rightIt);
        rightIt++;
    }
}

void margeSortSet(std::multiset<int> & s)
{
	int len = s.size();
	if (len <= 1)
		return;
	int mid = len / 2;
	std::multiset<int> left(s.begin(), std::next(s.begin(), mid));
	std::multiset<int> right(std::next(s.begin(), mid), s.end());
	margeSortSet(left);
	margeSortSet(right);
	s.clear();
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

void fillMultiset(std::list<int> & input, std::multiset<int> & s)
{
	for (std::list<int>::iterator it = input.begin(); it != input.end(); it++)
		s.insert(*it);
}

void		pmergeMe::margeSort()
{
	clock_t start = clock();
	fillList(this->_input, this->_l);
	margeSortList(this->_l);
	clock_t end = clock();
	this->_timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	fillMultiset(this->_input, this->_s);
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
	std::cout << "After:  ";
	std::multiset<int>::iterator it = this->_s.begin();
	for (size_t i = 0; i < this->_s.size(); i++)
	{
		std::cout << *it;
		if (i < this->_s.size() - 1)
			std::cout << " ";
		it++;
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << this->_l.size()
	<< " elements with std::list :     " << std::fixed << std::setprecision(6)
	<< this->_timeList << " us" << std::endl;

	std::cout << "Time to process a range of " << this->_s.size()
	<< " elements with std::multiset : " << std::fixed << std::setprecision(6)
	<< this->_timeSet << " us" << std::endl;
}
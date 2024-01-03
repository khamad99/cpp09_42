/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:42:48 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/03 13:28:08 by kalshaer         ###   ########.fr       */
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
		this->_input = rhs._input;
		this->_l = rhs._l;
		this->_s = rhs._s;
		this->_timeList = rhs._timeList;
		this->_timeSet = rhs._timeSet;
	}
	return (*this);
}



static void insertSortedList(std::list<int> & largElms, int element)
{
	 std::list<int>::iterator it = std::lower_bound(largElms.begin(), largElms.end(), element);
	 largElms.insert(it, element);
}

statc void	mergeSet(std::list<int> &largElms, std::list<int> &smallElms, std::list<int> & l)
{
	
}

static void margeSortList(std::list<int> & l)
{
	if ( l.size() <= 1)
		return ;

	std::list<int> largElms;
	std::list<int> smallElms;

	std::list<int>::iterator it = l.begin();
	while (it != l.end())
	{
		largElms.push_back(std::max(*it, *(++it));
		smallElms.push_back(std::min(*it, *(++it));
		l.pop_front();
		l.pop_front();
	}
	margeSortList(largElms);
	margeSortList(smallElms);

	it = l.begin();
	while (it != l.end())
	{
		insertSortedList(largElms, *it);
		++it;
		if (it != l.end())
			++it;
	}
	l.clear();
	l = std::move(largElms);
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
	<< " elements with std::list :     " << std::fixed << std::setprecision(6)
	<< this->_timeList << " us" << std::endl;

	std::cout << "Time to process a range of " << this->_s.size()
	<< " elements with std::multiset : " << std::fixed << std::setprecision(6)
	<< this->_timeSet << " us" << std::endl;

	if (std::is_sorted(this->_l.begin(),this->_l.end()))
		std::cout << "list sorted" << std::endl;
	if (std::is_sorted(this->_s.begin(),this->_s.end()))
		std::cout << "multiset sorted" << std::endl;
}
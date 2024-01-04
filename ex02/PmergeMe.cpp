/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:42:48 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/04 10:05:34 by kalshaer         ###   ########.fr       */
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

static void	margeSortLiStart(std::list<int> & l,
	std::list<int> & large,
	std::list<int> & small,
	int & pair)
{
	std::list<int>::iterator it = l.begin();
	while (next(it) != l.end())
	{
		int first = *it;
		int second = *next(it);
		if (first > second)
		{
			large.push_back(first);
			small.push_back(second);
		}
		else
		{
			large.push_back(second);
			small.push_back(first);
		}
		if ((first > second && second < pair))
			pair = second;
		else if ((first < second && first < pair))
			pair = first;
		l.pop_front();
		l.pop_front();
		it = l.begin();
	}
	if (l.size() == 1)
	{
		large.push_back(l.front());
		l.pop_front();
	}
}

static void	margeSortListBinary(std::list<int> & small,
	std::list<int> & large,
	std::list<int> & l)
{
	std::list<int>::iterator it = small.begin();
	std::list<int>::iterator it2;
	
	int pair = large.front();
	while (it != small.end())
	{
		if (pair == *it)
			it = std::next(it);
		if (it == small.end())
			break;
		it2 = std::lower_bound(large.begin(), large.end(), *it);
		large.insert(it2, *it);
		it = std::next(it);
	}
	l.clear();
	l = large;
}

static void mergeSortMultiSetBinary(std::multiset<int>& small,
	std::multiset<int>& large,
	std::multiset<int>& l)
{
	std::multiset<int>::iterator it = small.begin();
	int pair = *large.begin();
	while (it != small.end()) {
		if (pair == *it)
			it = std::next(it);
		if (it == small.end())
			break;
		std::multiset<int>::iterator it2 = large.lower_bound(*it);
		large.insert(it2, *it);
		it = std::next(it);
	}
	l.clear();
	l = large;
}

static void mergeSortMultiSetStart(std::multiset<int>& l,
	std::multiset<int>& large,
	std::multiset<int>& small,
	int& pair)
{
	std::multiset<int>::iterator it = l.begin();
	std::multiset<int>::iterator nextIt;
	while (it != l.end())
	{
		int first = *it;
		nextIt = std::next(it);
		if (nextIt != l.end())
		{
			int second = *nextIt;
			if (first > second)
			{
				large.insert(first);
				small.insert(second);
			}
			else
			{
				large.insert(second);
				small.insert(first);
			}
			if ((first > second && second < pair))
				pair = second;
			else if ((first < second && first < pair))
				pair = first;
			l.erase(it);
			l.erase(nextIt);
			it = l.begin();
		}
		else
		{
			large.insert(first);
			l.erase(it);
			break;
		}
	}
	l.clear();
	l = large;
}

void		pmergeMe::margeSort()
{
	int flag = 0;
	clock_t start = clock();
	std::list<int> large;
	std::list<int> small;
	int pair = std::numeric_limits<int>::max();
	fillList(this->_input, this->_l);
	if (this->_l.size() <= 3)
	{
		flag = 1;
		margeSortList(this->_l);
	}
	else if (flag == 0)
	{
		margeSortLiStart(this->_l, large, small, pair);
		margeSortList(large);
		large.push_front(pair);
		margeSortListBinary(small, large, this->_l);
	}
	clock_t end = clock();
	this->_timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	

	start = clock();
	std::multiset<int> smallset;
	std::multiset<int> largeset;
	pair = std::numeric_limits<int>::max();
	fillMultiset(this->_input, this->_s);
	if (flag == 1)
		margeSortSet(this->_s);
	else
	{
		mergeSortMultiSetStart(this->_s, largeset, smallset, pair);
		margeSortSet(largeset);
		largeset.insert(pair);
		mergeSortMultiSetBinary(smallset, largeset, this->_s);
	}
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

	// if (std::is_sorted(this->_l.begin(),this->_l.end()))
	// 	std::cout << "list sorted" << std::endl;
	// if (std::is_sorted(this->_s.begin(),this->_s.end()))
	// 	std::cout << "multiset sorted" << std::endl;
}
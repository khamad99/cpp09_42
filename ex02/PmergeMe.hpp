/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:34:54 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/04 10:01:16 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <list>
# include <set>
# include <unordered_set>
# include <algorithm>
# include <iterator>
# include <sstream>
# include <limits>
# include <cmath>
# include <ctime>
# include <cstdlib>

/*
std::list 
1- is linked list 
2- bidirectional iterator can access the data in both directions
3- keep the order of insertion

std::multiset
1- is binary search tree
2- it have direct access to the data in any place
3- keep the order of insertion


the list is faster than multiset in insertion and deletion for 1500 and less
1- list is O(1) for insertion and deletion because it is linked list using merge sort
2- multiset is O(log(n)) for insertion and deletion because it is binary search tree using merge sort

the multiset is faster than list in insertion and deletion for 1500 and more
1- list is O(n) for insertion and deletion because it is linked list using binary search
2- multiset is O(log(n)) for insertion and deletion because it is binary search tree using binary search

*/

class pmergeMe
{
	private:
		std::list<int>		_input;
		std::list<int>		_l;
		std::multiset<int>	_s;
		double				_timeList;
		double				_timeSet;

		pmergeMe();
	public:
		pmergeMe(const pmergeMe & src);
		pmergeMe & operator=(const pmergeMe & rhs);
		~pmergeMe();
		pmergeMe(std::list<int> & input_list);
		void		margeSort();
		void		print();
};

#endif
	
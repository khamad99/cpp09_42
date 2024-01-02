/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:34:54 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 14:59:57 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <list>
# include <deque>
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
3- keep the duplicates
4- keep the order of insertion

std::deque
1- is double-ended queue (array of arrays) 
2- random access iterator can access the data in both directions
3- keep the duplicates
4- keep the order of insertion

the list is slower than deque because 
1- the list is linked list and the deque is array of arrays
2- the list is bidirectional iterator and the deque is random access iterator
3- the list is slower than deque in insertion and deletion
*/

class pmergeMe
{
	private:
		std::list<int>		_input;
		std::list<int>		_l;
		std::deque<int>		_s;
		double				_timeList;
		double				_timeSet;
		pmergeMe();
		pmergeMe(const pmergeMe & src);
		pmergeMe & operator=(const pmergeMe & rhs);
	public:
		~pmergeMe();
		pmergeMe(std::list<int> & input_list);
		void		margeSort();
		void		print();
};

#endif
	
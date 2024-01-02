/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:34:54 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 09:03:05 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <list>
# include <set>
# include <algorithm>
# include <iterator>
# include <sstream>
# include <limits>
# include <cmath>
# include <ctime>
# include <cstdlib>
# include <deque>


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
	
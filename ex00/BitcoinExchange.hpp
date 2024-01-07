/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:31:31 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/05 10:02:44 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
std::vector to store the data from the file because 
1- I need to keep the order of the data as it is in the file
2- It accepts duplicates
3- It accpts pairs
4- it can be resized at runtime

std::map to store the data from the file because 
1- I need to be able to access the data by date 
2- it have a find() method 
3- it is sorted by key
4- it does not accept duplicates
*/

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <iomanip>
# include <cmath>
# include <limits>
# include <sstream>
# include <fstream>
# include <vector>
# include <map>
# include <algorithm>
#include <sys/stat.h>
#include <cstdlib>

# define SPC ' '
# define TAB '\t'
# define LF '\n'
# define VT '\v'
# define FF '\f'
# define CR '\r'


class BitcoinExchange
{
	private:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const & src);
		~BitcoinExchange();
		BitcoinExchange & operator=(BitcoinExchange const & src);
	public:

		static void		exchange(std::string date, float value, std::map<std::string, float> &database, int flag);
		static bool		check_date_format(std::string date, int flag);
};

#endif
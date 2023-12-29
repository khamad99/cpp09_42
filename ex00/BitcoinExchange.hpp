/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:31:31 by kalshaer          #+#    #+#             */
/*   Updated: 2023/12/29 09:47:50 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

		static void		exchange(std::vector<std::pair<std::string, float> > &data,
			std::map<std::string, float> &database);
};

#endif
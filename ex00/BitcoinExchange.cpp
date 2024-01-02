/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:32:06 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 10:52:18 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & src)
{
	if (this != &src)
	{
	}
	return (*this);
}

static bool btc_check_value_format(float value)
{
	if (value < 0)
		return (std::cout << "Error: not a positive number." << std::endl, false);
	else if (value > 1000)
		return (std::cout << "Error: too large a number." << std::endl, false);
	return (true);
	
}

static bool btc_check_date_format(std::string date)
{
		std::tm time = {};
		std::istringstream ss(date);
		ss >> std::get_time(&time, "%Y-%m-%d");
		if (ss.fail())
			return (std::cout << "Error: bad input => " << date << std::endl, false);
		std::time_t time_t = std::mktime(&time);
		if (time_t == -1 
		|| std::atoi((date.substr(0, 4)).c_str()) < 2009
		|| std::atoi((date.substr(0, 4)).c_str()) > 2023
		|| date == "2009-01-01")
			return (std::cout << "Error: bad input => " << date << std::endl, false);
		return (true);




	// if (date.size() != 10
	// || date[4] != '-'
	// || date[7] != '-'
	// || date.find_first_not_of("0123456789-") != std::string::npos
	// || std::atoi((date.substr(0, 4)).c_str()) < 2009
	// || std::atoi((date.substr(0, 4)).c_str()) > 2023
	// || date == "2009-01-01"
	// || std::atoi((date.substr(5, 2)).c_str()) < 1
	// || std::atoi((date.substr(5, 2)).c_str()) > 12
	// || std::atoi((date.substr(8, 2)).c_str()) < 1
	// || (std::atoi((date.substr(8, 2)).c_str()) > 31
	// && (std::atoi((date.substr(5, 2)).c_str()) == 1 || std::atoi((date.substr(5, 2)).c_str()) == 3
	// || std::atoi((date.substr(5, 2)).c_str()) == 5 || std::atoi((date.substr(5, 2)).c_str()) == 7
	// || std::atoi((date.substr(5, 2)).c_str()) == 8 || std::atoi((date.substr(5, 2)).c_str()) == 10
	// || std::atoi((date.substr(5, 2)).c_str()) == 12))
	// || (std::atoi((date.substr(8, 2)).c_str()) > 30
	// && (std::atoi((date.substr(5, 2)).c_str()) == 4 || std::atoi((date.substr(5, 2)).c_str()) == 6
	// || std::atoi((date.substr(5, 2)).c_str()) == 9 || std::atoi((date.substr(5, 2)).c_str()) == 11))
	// || (std::atoi((date.substr(8, 2)).c_str()) > 28
	// && std::atoi((date.substr(5, 2)).c_str()) == 2))
	// 	return (std::cout << "Error: bad input => " << date << std::endl, false);
	// return (true);
	
}

static	float btc_find_date_in_database(std::string date,
	std::map<std::string, float> &database)
{
	int										deference = std::numeric_limits<int>::max();
	int										tmp = 0;
	std::map<std::string, float>::iterator	it_database;
	std::map<std::string, float>::iterator	closest = database.begin();

	it_database = database.find(date);
	if (it_database != database.end())
		return (it_database->second);
	for (it_database = database.begin(); it_database != database.end(); it_database++)
	{
		std::tm time1 = {};
		std::tm time2 = {};
		std::istringstream ss1(date);
		std::istringstream ss2(it_database->first);
		ss1 >> std::get_time(&time1, "%Y-%m-%d");
		ss2 >> std::get_time(&time2, "%Y-%m-%d");
		std::time_t time1_t = std::mktime(&time1);
		std::time_t time2_t = std::mktime(&time2);

		if (time1_t != -1 && time2_t != -1)
		{
			tmp = std::difftime(time1_t, time2_t);
			if (tmp >= 0 && tmp < deference) {
				deference = tmp;
				closest = it_database;
			}
		}
	}
	return (closest->second);
}

void	BitcoinExchange::exchange(std::vector<std::pair<std::string, float> > &data,
	std::map<std::string, float> &database)
{
	float									value;

	std::vector<std::pair<std::string, float> >::iterator it_data = data.begin();

	for (it_data = data.begin(); it_data != data.end(); it_data++)
	{
		if (btc_check_date_format(it_data->first) == false
			|| btc_check_value_format(it_data->second) == false)
			continue ;
		value = btc_find_date_in_database(it_data->first, database);
		std::cout << it_data->first << " => " << it_data->second << " = " << (value * it_data->second) << std::endl;
	}

}

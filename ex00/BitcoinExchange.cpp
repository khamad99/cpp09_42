/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:32:06 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/10 13:21:42 by kalshaer         ###   ########.fr       */
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
	// std::cout << "closest date => " << closest->first << " = " << closest->second << "---------";
	return (closest->second);
}

bool BitcoinExchange::check_date_format(std::string date, int flag)
{
	if (date.size() != 10
	|| date[4] != '-'
	|| date[7] != '-'
	|| date.find_first_not_of("0123456789-") != std::string::npos)
	{
		if (flag == 0)
			return (std::cout << "Error: bad input => " << date << std::endl, false);
		else
			return (std::cout << "Error: invalid input in database file" << std::endl, false);
	}

	int day = std::atoi((date.substr(8, 2)).c_str());
	int month = std::atoi((date.substr(5, 2)).c_str());
	int year = std::atoi((date.substr(0, 4)).c_str());
	int is_leap_year = (year % 4 == 0 || (year % 100 == 0 && year % 400 == 0));
	if (date == "2009-01-01"
		|| year < 2009 || year > 2023
		|| month < 1 || month > 12
		|| day < 1
		|| (day > 31
		&& (month == 1 || month == 3 || month == 5 || month == 7
		|| month == 8 || month == 10 || month == 12))
		|| (day > 30
		&& (month == 4 || month == 6 || month == 9 || month == 11))
		|| (day > 29 && month == 2 && is_leap_year)
		|| (day > 28 && month == 2 && !is_leap_year))
	{
		if (flag == 0)
			std::cout << "Error: bad input => " << date << std::endl;
		return (false);
	}


	return (true);
}

void	BitcoinExchange::exchange(std::string date,
	float value,
	std::map<std::string, float> &database,
	int flag)
{
	float	price;

	if (flag == 0)
	{
		if (check_date_format(date, 0) == false)
			return ;
		std::cout << "Error: no delimiter" << std::endl;
			return;
	}

	if (flag == 1)
	{
		if (check_date_format(date, 0) == false)
			return ;
		std::cout << "Error: no value" << std::endl;
			return ;
	}

	if (check_date_format(date, 0) == false
		|| btc_check_value_format(value) == false)
		return ;
	price = btc_find_date_in_database(date, database);
	std::cout << date << " => " << value << " = " << (value * price) << std::endl;
}

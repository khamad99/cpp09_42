/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:39:27 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 10:13:06 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	ft_isspace(char c)
{
	if (c == SPC || c == TAB || c == LF
		|| c == VT || c == FF || c == CR)
		return (0);
	return (1);
}

std::string strtrim_space(std::string str)
{
	std::string::size_type	i;
	std::string::size_type	j;

	i = 0;
	j = str.size() - 1;
	while (i < str.size() && !ft_isspace(str[i]))
		i++;
	while (j > 0 && !ft_isspace(str[j]))
		j--;
	if (i > j)
		return ("");
	return (str.substr(i, j - i + 1));
}

static void	btc_prs_input_line(std::string line,
	std::vector<std::pair<std::string, float> > *data,
	std::map<std::string, float> *database,
	std::string delim)
{
	std::string::size_type	pos;
	std::string				tmp1;
	std::string				tmp2;
	float					value;
	std::string				date;

	pos = line.find(delim);
	if (pos == std::string::npos && line.size() == 0)
	{
		if (data != NULL)
			data->push_back(std::pair<std::string, float>("empty", 0));
		else
			database->insert(std::pair<std::string, float>("empty", 0));
		return	;
	}
	else if (pos == std::string::npos && line.size() != 0)
	{
		if (data != NULL)
			data->push_back(std::pair<std::string, float>(line, 0));
		else
			database->insert(std::pair<std::string, float>(line, 0));	
		return	;
	}
	tmp1 = strtrim_space(line.substr(0, pos));
	tmp2 = strtrim_space((line.substr(pos + 1, line.size())).c_str());
	if (tmp1.size() == 0 && tmp2.size() == 0)
	{
		if (data != NULL)
			data->push_back(std::pair<std::string, float>("empty", 0));
		else
			database->insert(std::pair<std::string, float>("empty", 0));
		return	;
	}
	else if (tmp1.size() == 0 && tmp2.size() != 0)
	{
		value = std::atof(tmp2.c_str());
		if (value == 0.0 && tmp2[0] != '0'
		&& tmp2.find_first_not_of("0123456789.") != std::string::npos)
			data->push_back(std::pair<std::string, float>("empty", 0));
		else if (data != NULL)
			data->push_back(std::pair<std::string, float>("empty", value));
		else
			database->insert(std::pair<std::string, float>("empty", value));
		return	;
	}
	else if (tmp1.size() != 0 && tmp2.size() == 0)
	{
		if (data != NULL)
			data->push_back(std::pair<std::string, float>(tmp1, 0));
		else
			database->insert(std::pair<std::string, float>(tmp1, 0));
		return	;
	}
	else
	{
		value = std::atof(tmp2.c_str());
		if (value == 0.0 && tmp2[0] != '0'
		&& tmp2.find_first_not_of("0123456789.") != std::string::npos)
			data->push_back(std::pair<std::string, float>(tmp1, 0));
		else if (data != NULL)
			data->push_back(std::pair<std::string, float>(tmp1, value));
		else
			database->insert(std::pair<std::string, float>(tmp1, value));
	}
}

static bool	btc_prs_input_head(std::string line, std::string delim)
{
	std::string::size_type	pos;
	std::string				tmp1;
	std::string				tmp2;

	if (line.size() == 0)
		return (false);
	pos = line.find(delim);
	if (pos == std::string::npos)
		return (false);
	tmp1 = strtrim_space(line.substr(0, pos));
	tmp2 = strtrim_space(line.substr(pos + 1, line.size()));
	if ((delim == "|" && tmp1 == "date" && tmp2 == "value" )
	|| (delim == "," && tmp1 == "date" && tmp2 == "exchange_rate"))
		return (true);
	else
		return (false);
}

static	void	btc_prs_input_file(std::string str, 
	std::vector<std::pair<std::string, float> > *data,
	std::map<std::string, float> *database,
	std::string delim)
{
	std::ifstream	ifs(str.c_str());
	std::string		line;

	if (ifs.is_open())
	{
		std::getline(ifs, line);
		if (!btc_prs_input_head(line, delim))
		{
			std::cerr << "Error: invaled header"; 
			if (delim == "|")
				std::cerr << " in input file";
			else
				std::cerr << " in database file";
			std::cerr << std::endl;
			exit(EXIT_FAILURE) ;
		}
		while (std::getline(ifs, line))
			btc_prs_input_line(strtrim_space(line), data, database, delim);
		ifs.close();
	}
	else
	{
		std::cerr << "Error: can't open";
		if (delim == "|")
			std::cerr << " input file";
		else
			std::cerr << " database file";
		std::cerr<< std::endl;
		exit(EXIT_FAILURE) ;
	}
	
}

int main(int ac, char **av)
{
	std::vector<std::pair<std::string, float> > data;
	std::map<std::string, float> database;

	if (ac != 2)
		return (std::cout << "Usage: ./btc [file]" << std::endl, 1);

	btc_prs_input_file(av[1], &data, NULL, "|");
	if (data.size() == 0)
	{
		std::cerr << "Error: empty input file" << std::endl;
		exit(EXIT_FAILURE) ;
	}
	btc_prs_input_file("data.csv", NULL, &database, ",");
	if (database.size() == 0)
	{
		std::cerr << "Error: empty database file" << std::endl;
		exit(EXIT_FAILURE) ;
	}
	BitcoinExchange::exchange(data, database);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:39:27 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/13 11:19:17 by kalshaer         ###   ########.fr       */
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

static int	btc_prs_input_line(std::string line,
	std::map<std::string, float> *database,
	std::string delim)
{
	std::string::size_type	pos;
	std::string				tmp1;
	std::string				tmp2;
	float					value;
	std::string				date;
	int						flag = 0;

	pos = line.find(delim);
	if (pos == std::string::npos && line.size() == 0)
	{
		if (delim == "|")
		{
			std::cout << "Error: empty line" << std::endl;
			return (0);
		}
		else
			flag = 1;
	}
	else if (pos == std::string::npos && line.size() != 0)
	{
		if (delim == "|")
		{
			BitcoinExchange::exchange(line, 0, *database, 0);
			return (0);
		}
		else
			flag = 1;	
	}
	if (flag == 1)
		return (1);
	tmp1 = strtrim_space(line.substr(0, pos));
	tmp2 = strtrim_space((line.substr(pos + 1, line.size())).c_str());
	if (tmp1.size() == 0 && tmp2.size() == 0)
	{
		if (delim == "|")
		{
			std::cout << "Error: no date and value" << std::endl;
			return (0);
		}
		else
			flag = 1;
	}
	else if (tmp1.size() == 0 && tmp2.size() != 0)
	{
		if (delim == "|")
		{
			std::cout << "Error: no date" << std::endl;
			return (0);
		}
		else
			flag = 1;
	}
	else if (tmp1.size() != 0 && tmp2.size() == 0)
	{
		if (delim == "|")
		{
			BitcoinExchange::exchange(tmp1, 0, *database, 1);
			return (0);
		}
		else
			flag = 1;
	}
	else
	{
		int f_flag = 0;
		std::stringstream	ss(tmp2);
		std::string::iterator sit = std::find(tmp2.begin(), tmp2.end(), '.');
		if (sit != tmp2.end() && sit + 1 != tmp2.end() && !std::isdigit(*(sit + 1)))
			f_flag = 1;
		ss >> value;
		int is_fail = ss.fail();
		ss.get();
		if (f_flag || is_fail || ss.get() != -1 || tmp2.find_first_not_of("0123456789.+-f") != std::string::npos
			|| std::count(tmp2.begin(), tmp2.end(), '.') > 1
			|| tmp2.find_last_not_of("0123456789f") == tmp2.size() - 1
			|| tmp2.find_first_not_of("+0123456789") == 0)
		{
			if (delim == "|")
			{
				if (BitcoinExchange::check_date_format(tmp1, 0) == false)
					return (0);
				std::cout << "Error: bad value" << " => " << tmp2 << std::endl;
				return (0);
			}
			else
				flag = 1;
		}
		else if (delim == "|")
			BitcoinExchange::exchange(tmp1, value, *database, 2);
		else
		{
			if (BitcoinExchange::check_date_format(tmp1, 1) == false)
				return (1);
			if (value < 0.0 || value > std::numeric_limits<int>::max())
				return (1);
			database->insert(std::pair<std::string, float>(tmp1, value));
		}
	}
	if (flag == 1)
		return (1);
	return (0);
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

bool isDirectory(const std::string& path) {
	struct stat pathStat;
	if (stat(path.c_str(), &pathStat) != 0) 
		return false;
	return S_ISDIR(pathStat.st_mode);
}

static	int	btc_prs_input_file(std::string str,
	std::map<std::string, float> *database,
	std::string delim)
{
	std::string		line;

	if (isDirectory(str.c_str()))
	{
		std::cerr << "Error: " << str << " is a directory" << std::endl;
		exit(EXIT_FAILURE) ;
	}
	std::ifstream	ifs(str.c_str());
	if (ifs.is_open())
	{
		if (ifs.peek() == std::ifstream::traits_type::eof())
		{
			std::cerr << "Error: empty";
			if (delim == "|")
				std::cerr << " input file";
			else
				std::cerr << " database file";
			std::cerr << std::endl;
			ifs.close();
			return (1);
		}

		while (std::getline(ifs, line) && (line.size() == 0 || line.find_first_not_of(" \t\v\f\r") == std::string::npos))
			line.clear();
		if (!btc_prs_input_head(line, delim))
		{
			if (delim == "|")
				std::cout << "Error: invaled header in input file" << std::endl;
			else
			{
				std::cout << "Error: invaled header in database file"  << std::endl;
				ifs.close();
				return (1);
			}
		}
		while (std::getline(ifs, line))
		{
			if (btc_prs_input_line(strtrim_space(line), database, delim) == 1)
			{
				std::cerr << "Error: invalid input in database file" << std::endl;
				ifs.close();
				return (1);
			}
			line.clear();
		}
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
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	std::map<std::string, float> database;

	if (ac != 2)
		return (std::cout << "Usage: ./btc [file]" << std::endl, 1);

	if (btc_prs_input_file("data.csv", &database, ",") == 1)
		return (1);
	if (database.size() == 0)
	{
		std::cerr << "Error: empty database file" << std::endl;
		exit(EXIT_FAILURE) ;
	}

	if (btc_prs_input_file(av[1], &database, "|") == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:25:40 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/10 14:08:21 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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

static void	removeDuplicates(std::list<int> & list)
{
	std::unordered_set<int> uniqueSet;
	std::list<int>::iterator it = list.begin();

	while (it != list.end()) 
	{
		if (uniqueSet.insert(*it).second)
			++it;
		else
			it = list.erase(it);
	}
}

int main(int ac, char **av)
{
	if (ac <= 2 )
	{
		std::cout << "Usage: ./pmergeMe [int] [int] ..." << std::endl;
		return (0);
	}
	std::list<int>		input_list;
	std::string			input;
	std::stringstream	ss;
	int					n;
	int					i = 1;

	while (i < ac)
	{
		input = strtrim_space(av[i]);
		if (input.find_first_not_of("0123456789+ ") != std::string::npos)
		{
			std::cout << "Error: invalid input" << std::endl;
			return (0);
		}
		ss << input;
		ss >> n;
		int f_fail = ss.fail();
		int c = ss.get();
		if (f_fail || n < 0 || n > std::numeric_limits<int>::max() || c != -1)
		{
			if (c != ' ' || c != -1)
				std::cout << "Error: invalid input" << std::endl;
			return (0);
		}
		input_list.push_back(n);
		ss.clear();
		i++;
	}
	removeDuplicates(input_list);
	if (input_list.size() <= 1)
	{
		std::cout << "not enough unique numbers to sort" << std::endl;
		return (0);
	}
	pmergeMe p(input_list);
	p.margeSort();
	p.print();
	return (0);
}
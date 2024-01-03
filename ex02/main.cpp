/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:25:40 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/03 20:33:30 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
		input = av[i];
		if (input.find_first_not_of("0123456789+") != std::string::npos)
		{
			std::cout << "Error: invalid input" << std::endl;
			return (0);
		}
		ss << input;
		ss >> n;
		if (ss.fail() || n < 0 || n > std::numeric_limits<int>::max())
		{
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
	std::cout << "input size: " << input_list.size() << std::endl;
	pmergeMe p(input_list);
	p.margeSort();
	p.print();
	return (0);
}
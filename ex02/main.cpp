/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:25:40 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 09:09:47 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac == 1 )
	{
		std::cout << "Usage: ./pmergeMe [list of numbers]" << std::endl;
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
		if (input.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cout << "Error: invalid input" << std::endl;
			return (0);
		}
		ss << input;
		ss >> n;
		if (ss.fail() || n < 0)
		{
			std::cout << "Error: invalid input" << std::endl;
			return (0);
		}
		input_list.push_back(n);
		ss.clear();
		i++;
	}
	pmergeMe p(input_list);
	p.margeSort();
	p.print();
	return (0);
}
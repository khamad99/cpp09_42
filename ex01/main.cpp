/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 07:23:38 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/07 15:17:37 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

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

int main(int ac, char **av)
{
	if (ac != 2)
		return (std::cout << "Error: wrong number of arguments." << std::endl, 1);
	RPN::rpn(strtrim_space(av[1]));
	return (0);
}
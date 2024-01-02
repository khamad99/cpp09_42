/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 07:21:35 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 12:20:21 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(RPN const & src)
{
	*this = src;
}

RPN::~RPN()
{
}

RPN & RPN::operator=(RPN const & src)
{
	if (this != &src)
	{
	}
	return (*this);
}

static bool rpn_check_format(std::string str)
{
	if (str.size() == 0)
		return (std::cout << "Error: empty string." << std::endl, false);
	else if (str.find_first_not_of("0123456789.+-*/% ") != std::string::npos)
		return (std::cout << "Error: invalid character." << std::endl, false);
	else if (str.find_first_of("0123456789") == std::string::npos)
		return (std::cout << "Error: no numbers." << std::endl, false);
	else if (str.find_first_of("+-*/%") == std::string::npos)
		return (std::cout << "Error: no operators." << std::endl, false);
	else if (str.find_first_of("+-*/%") == str.size() - 1)
		return (std::cout << "Error: operator at the end." << std::endl, false);
	else if (str.find_first_of("+-*/%") == 0)
		return (std::cout << "Error: operator at the beginning." << std::endl, false);
	else if (str.find_first_of("+-*/%") == str.find_last_of("+-*/%"))
		return (std::cout << "Error: only one operator." << std::endl, false);
	return (true);
}

static void rpn_calc(std::string str)
{
	std::stack<float> stack;
	std::string tmp;
	float a;
	float b;
	float c;
	float nb;

	while (str.size() > 0)
	{
		tmp = str.substr(0, str.find_first_of(" "));
		if (tmp.size() == 1)
		{
			if (tmp.find_first_of("0123456789") != std::string::npos)
			{
				nb = std::atof(tmp.c_str());
				if (nb >= 10 || nb < 0)
				{
					std::cout << "Error: invalid number." << std::endl;
					return ;
				}
				stack.push(nb);
			}
			else
			{
				if (stack.size() < 2)
				{
					std::cout << "Error: not enough numbers." << std::endl;
					return ;
				}
				a = stack.top();
				stack.pop();
				b = stack.top();
				stack.pop();
				if (tmp == "+")
					c = b + a;
				else if (tmp == "-")
					c = b - a;
				else if (tmp == "*")
					c = b * a;
				else if (tmp == "/")
					c = b / a;
				else if (tmp == "%")
					c = std::fmod(b, a);
				stack.push(c);
			}
		}
		if (tmp.size() > 1 && tmp.find_first_of(" ") == std::string::npos)
		{
			nb = std::atof(tmp.c_str());
			if (nb >= 10 || nb < 0
			|| tmp.find_first_of(".") != std::string::npos)
			{
				std::cout << "Error: invalid number." << std::endl;
				return ;
			}
			if (tmp.find_first_of("0123456789") == std::string::npos)
			{
				std::cout << "Error: invalid input." << std::endl;
				return ;
			}
			else if (nb < 10 || nb > 0)
				stack.push(nb);
			else
			{
				std::cout << "Error: invalid formate." << std::endl;
				return ;
			}
		}
		if (str.find_first_of(" ") == std::string::npos)
			str.erase(0, str.size());
		else
			str.erase(0, str.find_first_of(" ") + 1);
	}
	if (stack.size() != 1)
	{
		std::cout << "Error: too many numbers." << std::endl;
		return ;
	}
	std::cout << stack.top() << std::endl;
}

void RPN::rpn(std::string str)
{
	if (rpn_check_format(str))
		rpn_calc(str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 07:21:35 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/07 15:16:32 by kalshaer         ###   ########.fr       */
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
	else if (str.find_first_of("0123456789") == std::string::npos && str.size() >= 1)
		return (std::cout << "Error: no numbers." << std::endl, false);
	else if (str.find_first_of("+-*/%") == std::string::npos && str.size() > 1)
		return (std::cout << "Error: no operators." << std::endl, false);
	return (true);
}

static void rpn_calc(std::string str)
{
	std::stack<float>	stack;
	std::string			tmp;
	std::stringstream	ss;
	float				a;
	float				b;
	float				c;
	int					nb;

	while (str.size() > 0)
	{
		tmp = str.substr(0, str.find_first_of(" "));
		if (tmp.size() == 1 && tmp.find_first_of("+-*/%") != std::string::npos)
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
		else if (tmp.find_first_not_of("0123456789+-") != std::string::npos)
		{
			std::cout << "Error: invalid input" << std::endl;
			return ;
		}
		else
		{
			if (tmp[tmp.size() - 1] == '-' || tmp[tmp.size() - 1] == '+')
			{
				std::cout << "Error: invalid input" << std::endl;
				return ;
			}
			ss << tmp;
			ss >> nb;
			if (ss.fail() || nb <= -10 || nb >= 10)
			{
				ss.clear();
				if (tmp.empty())
				{
					if (str.find_first_of(" ") == std::string::npos)
						str.erase(0, str.size());
					else
						str.erase(0, str.find_first_of(" ") + 1);
					continue ;
				}
				else
					std::cout << "Error: invalid input." << std::endl;
				return ;
			}
			stack.push(static_cast<float>(nb));
			ss.clear();
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

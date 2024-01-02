/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 07:19:24 by kalshaer          #+#    #+#             */
/*   Updated: 2024/01/02 14:25:43 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <cmath>

/*
std::stack to store the data from the file because
1- I need to use the LIFO principle
*/

class RPN
{
	private:
		RPN();
		RPN(RPN const & src);
		RPN & operator=(RPN const & src);
		~RPN();
	public:
		static void rpn(std::string str);
};

#endif
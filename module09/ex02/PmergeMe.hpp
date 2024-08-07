/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:53:26 by vshchuki          #+#    #+#             */
/*   Updated: 2024/08/09 18:51:17 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <string>
#include <vector>

// Text color macros
#define			TEXT_GREEN "\033[32m"
#define			TEXT_BLUE "\033[34m"
#define			TEXT_WHITE "\033[37m"

// Background color macros
#define			BG_RED "\033[41m"

// Reset macros
#define			RESET "\033[0m"

#define			EXIT_SUCCESS 0
#define			EXIT_FAILURE 1

enum LogType
{
	DEFAULT,
	ERROR,
	INFO,
	SUCCESS
};


class PmergeMe
{
	private:


	public:
		PmergeMe();
		PmergeMe(const char* argv[]);
		PmergeMe(const PmergeMe&);
		PmergeMe& operator=(const PmergeMe&);
		~PmergeMe();

		class Error : public std::exception
		{
			private:
				std::string message;

			public:
				Error(const std::string& message);
				std::string getMessage() const;
		};
		void						executeOnList();
		void						executeOnVector();
		static void					log(std::string message, LogType type = DEFAULT);
};
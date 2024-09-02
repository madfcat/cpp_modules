/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:53:26 by vshchuki          #+#    #+#             */
/*   Updated: 2024/09/02 21:21:16 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <chrono>
// #include <thread> // remove this
#include <algorithm>
// #include <variant> // remove this
// #include <memory> // remove this
#include <cmath>

#include <cstdarg>

// Rec value macros
#define 		EMPTY 0
#define 		NOT_INIT -1

// Text color macros
#define			TEXT_GREEN "\033[32m"
#define			TEXT_YELLOW "\033[33m"
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
	SUCCESS,
	DEBUG
};

enum ContType
{
	VECTOR,
	LIST
};


class PmergeMe
{
	public:
		class Rec
		{
			public:
				int mainChain;
				std::pair<Rec*, Rec*> pair;

				Rec();
				Rec(int value);
				Rec(int value, Rec* first, Rec* second);
				Rec(const Rec& other);
				Rec& operator=(const Rec& other);
				~Rec();
		};

	private:
		std::vector<std::string>						argv;
		std::vector<PmergeMe::Rec>						numVec;
		long long										vecUsecs = 0;
		std::list<PmergeMe::Rec>						numList;
		long long										listUsecs = 0;
		static const std::map<ContType, std::string>	containerTypes;


	public:
		PmergeMe();
		PmergeMe(const int argc, const char* argv[]);
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


		void						swapInit(std::vector<PmergeMe::Rec>& arr);
		std::vector<PmergeMe::Rec>	createInitPairs(std::vector<PmergeMe::Rec>& arr);
		void						insertAs(unsigned long& lastT, unsigned long& addAFromIndex,
										std::vector<PmergeMe::Rec>& newArr, std::vector<PmergeMe::Rec>& insertionArr);
		void						insertBs(unsigned long& lastT, unsigned long& addAFromIndex,
										std::vector<PmergeMe::Rec>& newArr, std::vector<PmergeMe::Rec>& insertionArr);
		std::vector<PmergeMe::Rec>	sortVec(std::vector<PmergeMe::Rec>& arr);
		std::vector<PmergeMe::Rec>	execute(ContType);
		void						run();

		/* Logging */
		template <typename T>
		void						printTime(T& container, ContType type, long long usecs) const;
		template <typename T>
		std::string					createSeq(T& container) const;
		void						printArr(std::vector<PmergeMe::Rec>& arr, std::string msg = "Base Pair");
		void						printEl(PmergeMe::Rec& el, std::string msg = "Base Pair");
		static void					log(std::string message, LogType type = DEFAULT);
};

std::ostream& operator<<(std::ostream& os, const PmergeMe::Rec& rec);

// template void PmergeMe::printInfo(std::vector<int>& container, ContType type, long long usecs) const;
// template void PmergeMe::printInfo(std::list<int>& container, ContType type, long long usecs) const;
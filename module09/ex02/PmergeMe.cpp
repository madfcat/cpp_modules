/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:53:23 by vshchuki          #+#    #+#             */
/*   Updated: 2024/09/02 15:08:48 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

const std::map<ContType, std::string> PmergeMe::containerTypes = {{VECTOR, "vector"}, {LIST, "list"}};

PmergeMe::PmergeMe()
{
	log("PmergeMe default constructor called", INFO);
}

PmergeMe::PmergeMe(const int argc, const char* argv[])
{
	log("PmergeMe constructor called", INFO);
	this->argv = std::vector<std::string>(argv + 1, argv + argc);
	for (int i = 1; i < argc; i++)
	{
		int newNum = std::stoi(argv[i]);
		auto it = std::find_if(this->numVec.begin(), this->numVec.end(), [newNum](const Rec& rec) {
			return rec.mainChain == newNum;
		});
		if (it != this->numVec.end()) {
			throw PmergeMe::Error("This element is not unique: " + std::to_string(newNum));
		}
	
		if (newNum <= 0)
			throw PmergeMe::Error("Not a positive number: " + std::to_string(newNum));

		this->numVec.emplace_back(newNum); // construct directly in the vector
		this->numList.emplace_back(newNum); // construct directly in the list
	}
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	log("PmergeMe copy constructor called", INFO);
	this->numVec = other.numVec;
	this->numList = other.numList;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	log("PmergeMe assignment operator called", INFO);
	if (this != &other)
	{
		this->numVec = other.numVec;
		this->numList = other.numList;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
	log("PmergeMe destructor called", INFO);
}

/* Methods */

std::vector<Rec>	PmergeMe::createInitPairs(std::vector<Rec>& arr)
{
	std::vector<Rec> newArr;
	for (unsigned long i = 1; i < arr.size(); i += 2)
	{
		newArr.emplace_back(arr[i].mainChain, &arr[i], &arr[i - 1]);
	}
	// Handle last element
	if (arr.size() % 2 == 1)
	{
		newArr.emplace_back(EMPTY, nullptr, &arr[arr.size() - 1]);
	}

	return newArr;
}

void PmergeMe::swapInit(std::vector<Rec>& arr)
{
	for (unsigned long i = 1; i < arr.size(); i += 2)
	{

		if (arr[i].mainChain < arr[i - 1].mainChain)
		{	
			std::swap(arr[i], arr[i - 1]);
		}
	}
}

unsigned long findBIndex(unsigned long arrSize, unsigned long k)
{
	unsigned long t = (std::pow(2, k + 1) + std::pow(-1, k)) / 3 - 1;
	t = t <= arrSize - 1 ? t : arrSize - 1;
	return t;
}


std::vector<Rec> PmergeMe::sortVec(std::vector<Rec>& arr)
{
	// Base case: return if less than 4 elements
	if (arr.size() <= 2)
	{
		swapInit(arr);
		// printArr(arr);
		return arr;
	}

	swapInit(arr);
	auto initSeq = createInitPairs(arr);

	printArr(initSeq);

	Rec leftOut;
	if (initSeq.back().mainChain == EMPTY)
	{
		leftOut = initSeq.back();
		initSeq.pop_back();
		printEl(leftOut, "Left Pair");
	}
	std::cout << "-------" << std::endl;
	printArr(initSeq);

	std::cout << "------- Let's start recursion1 -------" << std::endl;

	std::vector<Rec> newArr = sortVec(initSeq);

	/* Insertion sort */
	std::cout << "------- Before insertion -------" << std::endl;
	printArr(newArr);
	std::cout << "---" << std::endl;
	
	// Push back lefOut
	if (leftOut.mainChain == EMPTY)
	{
		newArr.push_back(leftOut);
		std::cout << "!! pushed leftOut: " << newArr.back().mainChain << std::endl;
	}
	// printArr(newArr, "Base pair after pushed leftOut");

	if (newArr[0].pair.first == nullptr) // top level
		return newArr;



	std::vector<Rec> insertionArr;
	insertionArr.emplace_back(*newArr[0].pair.second);
	insertionArr.emplace_back(*newArr[0].pair.first);
	
	unsigned long k = 2;
	unsigned long lastB = findBIndex(newArr.size(), k);
	unsigned long addAFrom = 1;

	while(42)
	{
		// Populate As
		std::cout << "addAFrom: " << addAFrom << ", lastB: "<< lastB<< std::endl;
		for (unsigned long i = addAFrom; i <= lastB; i++)
		{
			if (newArr[i].mainChain == EMPTY)
				continue;
			if (i < newArr.size() && newArr[i].pair.first != nullptr)
				insertionArr.emplace_back(*newArr[i].pair.first);
			else
			{
				insertionArr.emplace_back(newArr[i]);
			}
			std::cout << "pushed A: " << newArr[i].mainChain << std::endl;
		}
		std::cout << "here" << std::endl;

		printArr(insertionArr, "Base Pair populate A");

		std::cout << "----" << std::endl;
		// Insert Bs
		std::cout << "-- Now inserting Bs. lastB: " << lastB << ", till addFrom - 1: " << addAFrom - 1 << std::endl;
		for (unsigned long i = lastB; i != addAFrom - 1; i--)
		{
			unsigned long low = 0;
			unsigned long top = insertionArr.size() - 1;
			unsigned long mid = 0;

			while (low <= top)
			{
				mid = low + (top - low) / 2;  // Correct calculation of mid
				// std::cout << "i: " << i << ", size: " << newArr.size() << std::endl;
				// std::cout << "low: " << low << ", top: " << top << std::endl;
				// std::cout << "mid: " << mid << ", size: " << insertionArr.size() << std::endl;
				if (newArr[i].pair.second->mainChain < insertionArr[mid].mainChain)
				{
					if (mid == 0)
						break;  // Avoid underflow, no valid position to move `top` down
					top = mid - 1;
				}
				else
				{
					if (mid >= insertionArr.size() - 1)
						break;  // Avoid overflow, no valid position to move `low` up
					low = low == insertionArr.size() - 1 ? low : mid + 1;
				}
			}

			// Insert at the correct position
			insertionArr.insert(insertionArr.begin() + low, Rec(*newArr[i].pair.second));
			std::cout << "pushed B: " << newArr[i].pair.second->mainChain << std::endl;
		}
		std::cout << "--- Stop inserting Bs" << std::endl;

		// if (lastB <= insertionArr.size() - 1)
		addAFrom = lastB + 1;
		k++;
		lastB = findBIndex(newArr.size(), k);

		if (addAFrom > newArr.size() - 1)
		{

			std::cout << "break " << std::endl;
			break;
		}
		
	}
	printArr(insertionArr, "Base Pair before return");
	return insertionArr;
}



std::vector<Rec> PmergeMe::execute(ContType type)
{
	auto start = std::chrono::high_resolution_clock::now();

	// sort(this->numVec, this->numVec);
	std::vector<Rec> result = sortVec(this->numVec);

	// Simulate some work by sleeping for 1 second (1,000,000 microseconds)
	// std::this_thread::sleep_for(std::chrono::seconds(1));

	auto end = std::chrono::high_resolution_clock::now();

	switch (type)
	{
		case VECTOR:
			this->vecUsecs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			break;
		case LIST:
			this->listUsecs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			break;
	}
	return result;
}


void PmergeMe::run()
{
	log("Before: " + createSeq(this->argv), INFO);
	std::vector<Rec> result = execute(VECTOR);
	// execute(LIST);
	// log(std::string("After: ") + "put smth here lol", SUCCESS);
	log("After: " + createSeq(result), SUCCESS);
	printTime(this->numVec, VECTOR, this->vecUsecs);
	// printTime(this->numList, LIST, this->listUsecs);
}

void PmergeMe::printArr(std::vector<Rec>& arr, std::string msg)
{
	for (auto& el : arr)
	{
		printEl(el, msg);
	}
}

void PmergeMe::printEl(Rec& el, std::string msg)
{
	std::cout << "mainChain: " << el.mainChain
	<< " | " << msg <<": ("
	<< (el.pair.first ? std::to_string(el.pair.first->mainChain) : "null")
	<< ", "
	<< (el.pair.second ? std::to_string(el.pair.second->mainChain) : "null")
	<< ")" << std::endl; 
}

void PmergeMe::log(std::string message, LogType type)
{
	switch (type)
	{
		case INFO:
			std::cout << "ℹ️ " << TEXT_BLUE ;
			break;
		case ERROR:
			std::cout << "🚫 " << BG_RED << TEXT_WHITE ;
			break;
		case SUCCESS:
			std::cout << "✅ " << TEXT_GREEN ;
			break;
		case DEFAULT:
			break;
	}
	std::cout << message << RESET << std::endl;
}

/* Error */

std::string PmergeMe::Error::getMessage() const
{
	return this->message;
}

PmergeMe::Error::Error(const std::string& message)
{
	this->message = message;
}

std::ostream& operator<<(std::ostream& os, const Rec& rec)
{
	os << rec.mainChain;
	return os;
}
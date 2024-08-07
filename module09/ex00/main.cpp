/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:09:47 by vshchuki          #+#    #+#             */
/*   Updated: 2024/08/07 22:40:27 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <string>
#include <fstream>

int main(int argc, const char *argv[])
{
	try
	{
		if (argc != 2)
		{
			BitcoinExchange::log("Could not open file.", ERROR);
			BitcoinExchange::log("Usage: ./btc <filename>", INFO);
			return EXIT_FAILURE;
		}

		BitcoinExchange exchange(argv[1]);
	}
	catch (BitcoinExchange::ExchangeError& e)
	{
		BitcoinExchange::log(e.getMessage(), ERROR);
		return EXIT_FAILURE;
	}
	catch (std::exception& e)
	{
		BitcoinExchange::log(e.what(), ERROR);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

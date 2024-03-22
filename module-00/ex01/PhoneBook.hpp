/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:51:53 by vshchuki          #+#    #+#             */
/*   Updated: 2024/03/23 00:55:45 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# include "Contact.hpp"
# define MAX_CONTACTS 8

# include <iostream>
# include <cstring>

// Define ANSI escape codes for colors
# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

// Define ANSI escape codes for text decoration
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define ITALIC  "\033[3m"
#define UNDERLINE "\033[4m"

typedef void (Contact::*MemberFunction)(std::string);

class PhoneBook
{
	private:
		Contact	contacts[MAX_CONTACTS];
		int		currentIndex;

		void		printIntro(void) const;
		void		printErrorMessage(std::string message) const;
		std::string	truncateField(std::string fieldName) const;
		
		int 		addContactField(std::string msg, std::string& inputLine,  Contact& contact, MemberFunction func);
		void 		addContact(Contact& contact, int index);

		void 		incrementCurrentIndex();
		int			getCurrentIndex() const;

		int			showAllContacts() const;
		Contact&	getContact(int index);
		void		printContactInfo(int index);

		void		runAddCommand(void);
		void		runSearchCommand(void);
	
	public:
		PhoneBook();
		void		run(void);
};

#endif

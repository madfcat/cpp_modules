/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:54:08 by vshchuki          #+#    #+#             */
/*   Updated: 2024/08/22 14:06:15 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP
# include <iostream>
# include <string>
# include <stdexcept>
# include "AForm.hpp"

class AForm;

class Bureaucrat
{
	private:
		std::string					name = "Unknown";
		unsigned int				grade = 150;
		static const unsigned int	HighestGrade = 1;
		static const unsigned int	LowestGrade = 150;

	public:
		Bureaucrat();
		Bureaucrat(const std::string name, unsigned int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();


		void				signForm(AForm& form);
		void				executeForm(AForm const & form);

		void 				incrementGrade();
		void 				decrementGrade();

		const std::string	getName() const;
		unsigned int		getGrade() const;
		unsigned int		getHighestGrade() const;
		unsigned int		getLowestGrade() const;

	private:
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const noexcept;
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const noexcept;
		};
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif
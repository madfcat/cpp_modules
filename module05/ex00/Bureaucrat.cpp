/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:54:05 by vshchuki          #+#    #+#             */
/*   Updated: 2024/08/22 19:10:03 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
	std::cout << this->name << ": Bureaucrat default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string name, unsigned int grade): name(name), grade(grade)
{
	std::cout << this->name << ": Bureaucrat constructor called" << std::endl;
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
{
	std::cout << this->name << ": Bureaucrat copy constructor called" << std::endl;
	this->name = other.getName();
	this->grade = other.getGrade();
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	std::cout << this->name << ": Bureaucrat assignment operator called" << std::endl;
	if (this != &other)
	{
	this->name = other.getName();
	this->grade = other.getGrade();
	}
	return *this;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << this->name << ": Bureaucrat destructor called" << std::endl;
}

const std::string Bureaucrat::getName() const
{
	return this->name;
}

unsigned int Bureaucrat::getGrade() const
{
	return this->grade;
}

unsigned int Bureaucrat::getHighestGrade() const
{
	return this->HighestGrade;
}

unsigned int Bureaucrat::getLowestGrade() const
{
	return this->LowestGrade;
}

void Bureaucrat::incrementGrade()
{
	if (this->grade == getHighestGrade())
	{
		std::cout << "Highest grade can not be incremented" << std::endl;
		throw Bureaucrat::GradeTooHighException();
	}
	else
		this->grade--;
}
void Bureaucrat::decrementGrade()
{
	if (this->grade == getLowestGrade())
	{
		std::cout << "Lowest grade can not be decremented" << std::endl;
		throw Bureaucrat::GradeTooLowException();
	}
	else
		this->grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const noexcept
{
	return "❗️ Invalid grade. Grade is too high.";
}

const char* Bureaucrat::GradeTooLowException::what() const noexcept
{
	return "❗️ Invalid grade. Grade is too low.";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return os;
}

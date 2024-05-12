/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:40:35 by vshchuki          #+#    #+#             */
/*   Updated: 2024/05/12 02:22:55 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP
# ifndef ANIMAL_HPP
#  include "Animal.hpp"
# endif
# ifndef BRAIN_HPP
# include "Brain.hpp"
# endif
# include <iostream>

class Dog : public Animal
{
	private:
		Brain* brain;

	public:
		Dog();
		Dog(const Dog& other);
		Dog& operator=(const Dog& other);
		virtual ~Dog() override;
		
		virtual void	makeSound() const override;
		Brain*			getBrain() const;
};

#endif
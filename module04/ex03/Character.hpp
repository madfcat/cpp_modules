/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:55:29 by vshchuki          #+#    #+#             */
/*   Updated: 2024/05/08 14:09:37 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP
# ifndef ICHARACTER_HPP
#  include "ICharacter.hpp"
# endif
# include <iostream>
# include <string>

class Character: public ICharacter
{
	private:
		std::string name;
		static const int inventorySize = 4;
		AMateria *inventory[inventorySize];

	public:
		Character();
		Character(const Character& other);
		Character& operator=(const Character& other);
		~Character() override;

		Character(std::string const & name);

		std::string const & getName() const override;
		void equip(AMateria* m) override;
		void unequip(int idx) override;
		void use(int idx, ICharacter& target) override;

		AMateria* getInventory(int idx) const;
};

#endif
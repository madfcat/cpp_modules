/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:51:53 by vshchuki          #+#    #+#             */
/*   Updated: 2024/05/03 15:35:48 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP
# ifndef AMATERIA_HPP
#  include "AMateria.hpp"
# endif
# ifndef IMATERIASOURCE_HPP
#  include "IMateriaSource.hpp"
# endif
# include <iostream>

class MateriaSource : public IMateriaSource
{
	private:
		static const int storageSize = 4;
		AMateria* storage[storageSize];

	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		MateriaSource& operator=(const MateriaSource& other);

		~MateriaSource() override;
		void learnMateria(AMateria*) override;
		AMateria* createMateria(std::string const & type) override;
};

#endif
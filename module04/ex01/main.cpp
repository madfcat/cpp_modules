/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:35:23 by vshchuki          #+#    #+#             */
/*   Updated: 2024/05/07 17:31:13 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

template <typename T>
void fill_ideas(int n, T animal)
{
	for (int i = 0; i < 100; i++)
		animal->getBrain()->setIdea(i, animal->getType() + " #" + std::to_string(n) + " Idea #" + std::to_string(i));
}

int main() {
	std::cout << "====== Test from PDF ======" << std::endl;
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		
		delete j;//should not create a leak
		delete i;
	}
	
	std::cout << std::endl;
	std::cout << "====== More tests ======" << std::endl;
	{
		const int n = 10;
		Animal* animals[n];

		for (int i = 0; i < n; i++)
		{
			if (i % 2 == 0)
			{
				animals[i] = new Dog();
				fill_ideas<Dog*>(i, dynamic_cast<Dog*>(animals[i]));
			}
			else
			{
				animals[i] = new Cat();
				fill_ideas<Cat*>(i, dynamic_cast<Cat*>(animals[i]));
			}
		}

		for (int i = 0; i < n; i++)
		{
			animals[i]->makeSound();
		}

		int animalsToIterate = 1; // n for max
		for (int j = 0; j < animalsToIterate; j++)
		{
			for (int i = 0; i < 100; i++)
			{
				if (animals[j]->getType() == "Dog")
					std::cout << i << ". "<< dynamic_cast<Dog*>(animals[j])->getBrain()->getIdea(i) << std::endl;
				else
					std::cout << i << ". "<< dynamic_cast<Cat*>(animals[j])->getBrain()->getIdea(i) << std::endl;
			}
		}

		for (int i = 0; i < n; i++)
			delete (animals[i]);
	}

	std::cout << std::endl;
	std::cout << "====== Shallow copy constructor test ======" << std::endl;
	{
		const int n = 2;
		Animal* animals[n];

		for (int i = 0; i < n; i++)
		{
			if (i % 2 == 0)
			{
				animals[i] = new Dog();
				fill_ideas<Dog*>(i, dynamic_cast<Dog*>(animals[i]));
			}
			else
			{
				animals[i] = new Cat();
				fill_ideas<Cat*>(i, dynamic_cast<Cat*>(animals[i]));
			}
		}
		Animal* copyDog = new Dog(*dynamic_cast<Dog*>(animals[0]));
		copyDog->makeSound();

		
		std::cout << "== Let's check copyDog and original" << std::endl;
		std::cout << dynamic_cast<Dog*>(copyDog)->getBrain()->getIdea(0) << std::endl;
		std::cout << dynamic_cast<Dog*>(animals[0])->getBrain()->getIdea(0) << std::endl;

		std::cout << "== Let's change copyDog and now check copyDog and original" << std::endl;
		dynamic_cast<Dog*>(copyDog)->getBrain()->setIdea(0, "New Dog Idea #15: Changed my mind with this idea!");
		std::cout << dynamic_cast<Dog*>(copyDog)->getBrain()->getIdea(0) << std::endl;
		std::cout << dynamic_cast<Dog*>(animals[0])->getBrain()->getIdea(0) << std::endl;
		std::cout << "== Now let's remove animals array" << std::endl;
		for (int i = 0; i < n; i++)
			delete (animals[i]);
		std::cout << "== And finally remove copyDog" << std::endl;
		delete (copyDog);
	}

	std::cout << std::endl;
	std::cout << "====== Shallow assignment constructor test ======" << std::endl;
	{
		const int n = 2;
		Animal* animals[n];

		for (int i = 0; i < n; i++)
		{
			if (i % 2 == 0)
			{
				animals[i] = new Dog();
				fill_ideas<Dog*>(i, dynamic_cast<Dog*>(animals[i]));
			}
			else
			{
				animals[i] = new Cat();
				fill_ideas<Cat*>(i, dynamic_cast<Cat*>(animals[i]));
			}
		}
		Animal* firstDog = new Dog();
		Dog& referenceDog = dynamic_cast<Dog&>(*firstDog);
		std::cout << "== Assignment operator: " << std::endl;
		referenceDog = dynamic_cast<Dog&>(*animals[0]);
		
		std::cout << "== Let's check referenceDog and original" << std::endl;
		std::cout << dynamic_cast<Dog&>(referenceDog).getBrain()->getIdea(15) << std::endl;
		std::cout << dynamic_cast<Dog*>(animals[0])->getBrain()->getIdea(15) << std::endl;

		std::cout << "== Let's change referenceDog and now check referenceDog and original" << std::endl;
		dynamic_cast<Dog&>(referenceDog).getBrain()->setIdea(15, "New Dog Idea #15: Changed my mind with this idea!");
		std::cout << dynamic_cast<Dog&>(referenceDog).getBrain()->getIdea(15) << std::endl;
		std::cout << dynamic_cast<Dog*>(animals[0])->getBrain()->getIdea(15) << std::endl;
		std::cout << "== Now let's remove animals array" << std::endl;
		for (int i = 0; i < n; i++)
			delete (animals[i]);
		delete (firstDog);
	}

	return (0);
}

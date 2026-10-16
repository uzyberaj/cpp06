/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:53:27 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/10/16 17:37:19 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "identify.hpp"

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

// Les classes sont vides : il n’y a pas de méthode virtuelle "identify" dans la classe.
// On identifie à l’extérieur avec dynamic_cast > but de l’exercice.

// Cree au hasard un objet A, B ou C sur le tas et le renvoie comme Base*.
// Le sujet laisse libre le choix du generateur aleatoire : on utilise rand().
Base*	generate(void)
{
	static bool	seeded = false;

	if (!seeded)
	{
		std::srand(static_cast<unsigned int>(std::time(0)));
		seeded = true;
	}

	switch (std::rand() % 3)
	{
		case 0:
			return new A();
		case 1:
			return new B();
		default:
			return new C();
	}
}

// Version pointeur : dynamic_cast renvoie NULL si le cast echoue.
// On teste donc le resultat du cast (pas d'exception ici).
void	identify(Base* p)
{
	if (p == 0)
		return ;

	if (dynamic_cast<A*>(p) != 0)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != 0)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != 0)
		std::cout << "C" << std::endl;
}

// Version reference : dynamic_cast echoue avec une exception (bad_cast).
// Le sujet interdit d'utiliser un pointeur dans cette fonction.

// 2 versions car c'est la règle du langage C++ :
// pointeur > échec silencieux (NULL) ;
// référence > pas de "référence nulle" > exception.

void	identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return ;
	}
	catch (std::exception& e)
	{
		(void)e;
	}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return ;
	}
	catch (std::exception& e)
	{
		(void)e;
	}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	}
	catch (std::exception& e)
	{
		(void)e;
	}
}

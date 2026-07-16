/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:53:40 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/07/16 16:53:41 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "identify.hpp"

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>

// Programme de test pour l'exercice 02.
// Chaque section illustre un point du sujet en lançant ./identify.

int	main()
{
	// === Test 1 : identify(Base*) sur un objet A ===
	// Sujet : afficher le vrai type via dynamic_cast sur un pointeur.
	// Attendu : "A"
	std::cout << "=== Test 1 : identify(Base*) — objet A ===" << std::endl;
	Base*	ptrA = new A();
	std::cout << "identify(ptrA) : ";
	identify(ptrA);
	delete ptrA;
	std::cout << std::endl;

	// === Test 2 : identify(Base*) sur un objet B ===
	std::cout << "=== Test 2 : identify(Base*) — objet B ===" << std::endl;
	Base*	ptrB = new B();
	std::cout << "identify(ptrB) : ";
	identify(ptrB);
	delete ptrB;
	std::cout << std::endl;

	// === Test 3 : identify(Base*) sur un objet C ===
	std::cout << "=== Test 3 : identify(Base*) — objet C ===" << std::endl;
	Base*	ptrC = new C();
	std::cout << "identify(ptrC) : ";
	identify(ptrC);
	delete ptrC;
	std::cout << std::endl;

	// === Test 4 : identify(Base&) sur un objet A ===
	// Sujet : version reference avec try/catch (pas de pointeur dans la fonction).
	// Attendu : "A"
	std::cout << "=== Test 4 : identify(Base&) — objet A ===" << std::endl;
	A		objA;
	std::cout << "identify(objA) : ";
	identify(objA);
	std::cout << std::endl;

	// === Test 5 : identify(Base&) sur un objet B ===
	std::cout << "=== Test 5 : identify(Base&) — objet B ===" << std::endl;
	B		objB;
	std::cout << "identify(objB) : ";
	identify(objB);
	std::cout << std::endl;

	// === Test 6 : identify(Base&) sur un objet C ===
	std::cout << "=== Test 6 : identify(Base&) — objet C ===" << std::endl;
	C		objC;
	std::cout << "identify(objC) : ";
	identify(objC);
	std::cout << std::endl;

	// === Test 7 : polymorphisme — Base* vers types derives ===
	// Sujet : le pointeur Base* doit quand meme reveler le type reel.
	std::cout << "=== Test 7 : polymorphisme (Base* vers A/B/C) ===" << std::endl;
	Base*	objects[3];
	objects[0] = new A();
	objects[1] = new B();
	objects[2] = new C();

	for (int i = 0; i < 3; ++i)
	{
		std::cout << "identify*(objects[" << i << "]) : ";
		identify(objects[i]);
		std::cout << "identify&(objects[" << i << "]) : ";
		identify(*objects[i]);
	}
	for (int i = 0; i < 3; ++i)
		delete objects[i];
	std::cout << std::endl;

	// === Test 8 : generate() — creation aleatoire + identification ===
	// Sujet : generate() instancie aleatoirement A, B ou C.
	// Attendu : chaque objet genere est identifie comme A, B ou C (les deux versions).
	std::cout << "=== Test 8 : generate() x10 (aleatoire) ===" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		Base*	generated = generate();

		std::cout << "Essai " << i + 1 << " — identify* : ";
		identify(generated);
		std::cout << "           identify& : ";
		identify(*generated);
		delete generated;
	}
	std::cout << std::endl;

	// === Test 9 : pointeur NULL ===
	// Cas limite : identify(Base*) avec NULL ne doit pas crasher.
	std::cout << "=== Test 9 : identify(Base*) avec NULL ===" << std::endl;
	std::cout << "identify(NULL) : (rien attendu)" << std::endl;
	identify(static_cast<Base*>(0));
	std::cout << "OK : pas de crash" << std::endl;

	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:52:24 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/10/16 16:46:26 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

#include <iostream>
#include <string>

// Lance une conversion et separe visuellement chaque cas en mode test.
static void	runTest(const std::string& label, const std::string& literal)
{
	std::cout << "=== " << label << " ===" << std::endl;
	std::cout << "Entree : " << literal << std::endl;
	ScalarConverter::convert(literal);
	std::cout << std::endl;
}

// Usage normal (comme dans le sujet) : ./convert <litteral>
// Sans argument : lance tous les tests
int	main(int argc, char** argv)
{
	if (argc == 2)
	{
		ScalarConverter::convert(argv[1]);
		return 0;
	}

	if (argc != 1)
	{
		std::cerr << "Usage: ./convert <litteral>" << std::endl;
		return 1;
	}

	std::cout << "Programme de test ScalarConverter (ex00)" << std::endl;
	std::cout << "Relancer un cas precis : ./convert <litteral>\n" << std::endl;

	// === Test 1 : exemple du sujet - entier 0 ===
	// Sujet : char non affichable, int/float/double a zero.
	// Attendu : Non displayable / 0 / 0.0f / 0.0
	runTest("Test 1 : exemple sujet - 0", "0");

	// === Test 2 : exemple du sujet - nan ===
	// Sujet : pseudo-litteral double nan, char et int impossibles.
	// Attendu : impossible / impossible / nanf / nan
	runTest("Test 2 : exemple sujet - nan", "nan");

	// === Test 3 : exemple du sujet - 42.0f ===
	// Sujet : litteral float, char affichable (ASCII 42 = '*').
	// Attendu : '*' / 42 / 42.0f / 42.0
	runTest("Test 3 : exemple sujet - 42.0f", "42.0f");

	// === Test 4 : litteral char 'a' ===
	// Sujet : format 'c' pour les caracteres.
	// Attendu : 'a' / 97 / 97.0f / 97.0
	runTest("Test 4 : litteral char 'a'", "'a'");

	// === Test 5 : entier positif ===
	runTest("Test 5 : entier 42", "42");

	// === Test 6 : entier negatif ===
	runTest("Test 6 : entier -42", "-42");

	// === Test 7 : float negatif avec decimale ===
	// Sujet : exemples de litteraux float (-4.2f).
	runTest("Test 7 : float -4.2f", "-4.2f");

	// === Test 8 : double avec decimale ===
	runTest("Test 8 : double 4.2", "4.2");

	// === Test 9 : pseudo-litteraux float ===
	runTest("Test 9 : nanf", "nanf");
	runTest("Test 10 : +inff", "+inff");
	runTest("Test 11 : -inff", "-inff");

	// === Test 12 : pseudo-litteraux double ===
	runTest("Test 12 : +inf", "+inf");
	runTest("Test 13 : -inf", "-inf");

	// === Test 14 : depassement int (overflow) ===
	// Sujet : conversion impossible si overflow.
	runTest("Test 14 : overflow int", "2147483648");

	// === Test 15 : char impossible (valeur hors plage) ===
	runTest("Test 15 : char impossible (128)", "128");

	// === Test 16 : int tronque (3.14) ===
	// Sujet : static_cast<int> tronque la partie decimale.
	runTest("Test 16 : int tronque (3.14)", "3.14");

	// === Test 17 : entree invalide ===
	runTest("Test 17 : entree invalide", "abc");

	return 0;
}

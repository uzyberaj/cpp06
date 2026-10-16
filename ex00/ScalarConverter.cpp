/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:52:33 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/10/16 16:45:36 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

#include <climits>
#include <cmath>
#include <cerrno>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

// Petite liste interne : une fois qu'on a lu le texte, on sait dans quelle
// "famille" il tombe (char, int, float ou double) avant de le convertir.
enum e_scalarType
{
	SCALAR_CHAR,
	SCALAR_INT,
	SCALAR_FLOAT,
	SCALAR_DOUBLE
};

// OCF en privé : le sujet + le module demandent ces fonctions, mais on ne doit
// jamais créer un ScalarConverter (constructeur privé dans le .hpp).
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

// Regarde si le texte ressemble à un littéral char C++ : 'a', 'Z', etc.
// Il faut exactement 3 caractères : quote, la lettre, quote.
// Exemple valide en argument : ./convert "'a'"  (les quotes protègent le shell)
static bool	isCharLiteral(const std::string& literal)
{
	return (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'');
}

// Mots spéciaux pour un float en C++ (pas de vraie valeur numérique normale).
// nanf = Not a Number, inff = infini positif ou négatif (le f = version float).
static bool	isPseudoFloat(const std::string& literal)
{
	return (literal == "nanf" || literal == "+inff" || literal == "-inff");
}

// Même idée que ci-dessus mais pour double : nan, +inf, -inf (sans f à la fin).
static bool	isPseudoDouble(const std::string& literal)
{
	return (literal == "nan" || literal == "+inf" || literal == "-inf");
}

// Devine quel type de littéral on nous a passé en string (avant de parser).
// L'ordre des if compte : on teste char et les cas spéciaux avant le reste.
// char > pseudo float > pseudo double > float > double > sinon int
static e_scalarType	detectType(const std::string& literal)
{
	if (isCharLiteral(literal))
		return SCALAR_CHAR;
	if (isPseudoFloat(literal))
		return SCALAR_FLOAT;
	if (isPseudoDouble(literal))
		return SCALAR_DOUBLE;
	if (literal.length() >= 2 && literal[literal.length() - 1] == 'f')
		return SCALAR_FLOAT;
	if (literal.find('.') != std::string::npos)
		return SCALAR_DOUBLE;
	return SCALAR_INT;
}

// Le texte est déjà reconnu comme char : on prend le caractère du milieu.
// Pour "'a'" on retourne 'a' (le byte entre les deux quotes).
static char	parseChar(const std::string& literal)
{
	return literal[1];
}

// Transforme une string float (ex. 42.0f, -4.2f, nanf) en vrai float.
// strtod lit le nombre ; on enlève le f final sauf pour nanf/inff.
// Si le texte est pourri ou trop grand -> throw pour afficher "impossible".
static float	parseFloat(const std::string& literal)
{
	if (literal == "nanf")
		return static_cast<float>(std::strtod("nan", NULL));
	if (literal == "+inff")
		return static_cast<float>(std::strtod("+inf", NULL));
	if (literal == "-inff")
		return -static_cast<float>(std::strtod("inf", NULL));

	std::string	withoutF = literal.substr(0, literal.length() - 1);
	char*		end;

	errno = 0;
	double	value = std::strtod(withoutF.c_str(), &end);
	if (*end != '\0' || errno == ERANGE)
		throw std::string("invalid float");
	return static_cast<float>(value);
}

// Transforme une string double (ex. 4.2, nan, +inf) en vrai double.
// Même principe que parseFloat : strtod + vérif que tout le texte a été lu.
static double	parseDouble(const std::string& literal)
{
	if (literal == "nan")
		return std::strtod("nan", NULL);
	if (literal == "+inf")
		return std::strtod("+inf", NULL);
	if (literal == "-inf")
		return -std::strtod("inf", NULL);

	char*	end;

	errno = 0;
	double	value = std::strtod(literal.c_str(), &end);
	if (*end != '\0' || errno == ERANGE)
		throw std::string("invalid double");
	return value;
}

// Utile pour l'affichage : 42.0 est un "entier affiché en décimal" (42.0f / 42.0).
// Si c'est nan ou inf, on ne force pas le .0
static bool	isWholeNumber(double value)
{
	double	intPart;

	if (std::isnan(value) || std::isinf(value))
		return false;
	return (std::modf(value, &intPart) == 0.0);
}

// Affiche la ligne float: ... (nanf, +inff, -inff, ou un nombre + f à la fin).
static void	printFloatValue(float value)
{
	if (std::isnan(value))
		std::cout << "nanf";
	else if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inff";
		else
			std::cout << "-inff";
	}
	else
	{
		std::ostringstream	oss;

		if (isWholeNumber(static_cast<double>(value)))
			oss << std::fixed << std::setprecision(1) << value;
		else
			oss << value;
		std::cout << oss.str() << "f";
	}
}

// Affiche la ligne double: ... (même logique que printFloatValue sans le f).
static void	printDoubleValue(double value)
{
	if (std::isnan(value))
		std::cout << "nan";
	else if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inf";
		else
			std::cout << "-inf";
	}
	else
	{
		std::ostringstream	oss;

		if (isWholeNumber(value))
			oss << std::fixed << std::setprecision(1) << value;
		else
			oss << value;
		std::cout << oss.str();
	}
}

// Affiche les 4 lignes char / int / float / double (c'est ici qu'on utilise static_cast).
//
// static_cast : "j'ai une valeur d'un type, je veux la voir comme un autre type".
// Exemple : static_cast<int>(3.9) donne 3 (on coupe les décimales, pas d'arrondi).
// Ce n'est pas du texte -> nombre (ca c'est strtod dans convert/parse). Le cast part
// d'un nombre deja en memoire et change sa "forme" (int, char, float, double).
//
// On travaille d'abord avec un double (asDouble) pour ne pas recopier 4 fois le code.
// Ensuite, pour chaque ligne, on verifie si la conversion a du sens (nan, inf, trop grand...)
// et seulement apres on fait static_cast vers le type a afficher.
static void	displayResults(double asDouble)
{
	std::cout << "char: ";
	if (std::isnan(asDouble) || std::isinf(asDouble)
		|| asDouble < 0.0 || asDouble > 127.0)
		std::cout << "impossible";
	else
	{
		char	c = static_cast<char>(static_cast<int>(asDouble));

		if (c < 32 || c > 126)
			std::cout << "Non displayable";
		else
			std::cout << "'" << c << "'";
	}
	std::cout << std::endl;

	std::cout << "int: ";
	if (std::isnan(asDouble) || std::isinf(asDouble)
		|| asDouble < static_cast<double>(INT_MIN)
		|| asDouble > static_cast<double>(INT_MAX))
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(asDouble);
	std::cout << std::endl;

	std::cout << "float: ";
	printFloatValue(static_cast<float>(asDouble));
	std::cout << std::endl;

	std::cout << "double: ";
	printDoubleValue(asDouble);
	std::cout << std::endl;
}

// Point d'entrée du sujet : une string = un littéral C++.
// 1) deviner le type  2) parser  3) static_cast vers les autres  4) afficher
void	ScalarConverter::convert(const std::string& literal)
{
	try
	{
		e_scalarType	type = detectType(literal);

		if (type == SCALAR_CHAR)
		{
			char	c = parseChar(literal);
			displayResults(static_cast<double>(static_cast<int>(c)));
		}
		else if (type == SCALAR_INT)
		{
			char*	end;

			errno = 0;
			double	d = std::strtod(literal.c_str(), &end);
			if (*end != '\0' || errno == ERANGE)
				throw std::string("invalid int");
			displayResults(d);
		}
		else if (type == SCALAR_FLOAT)
		{
			float	f = parseFloat(literal);
			displayResults(static_cast<double>(f));
		}
		else
		{
			double	d = parseDouble(literal);
			displayResults(d);
		}
	}
	catch (...)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}

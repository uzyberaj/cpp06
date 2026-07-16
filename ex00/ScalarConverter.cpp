/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:52:33 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/07/16 16:52:34 by ulyssezyber      ###   ########.fr       */
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

// --- Types reconnus par le programme ---
// On detecte d'abord le type du litteral, puis on convertit vers les 3 autres.
enum e_scalarType
{
	SCALAR_CHAR,
	SCALAR_INT,
	SCALAR_FLOAT,
	SCALAR_DOUBLE
};

// --- OCF privee : la classe ne doit jamais etre instanciee ---
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

// --- Detection du type du litteral ---
static bool	isCharLiteral(const std::string& literal)
{
	// Format attendu : 'a' (3 caracteres, quotes simples)
	return (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'');
}

static bool	isPseudoFloat(const std::string& literal)
{
	return (literal == "nanf" || literal == "+inff" || literal == "-inff");
}

static bool	isPseudoDouble(const std::string& literal)
{
	return (literal == "nan" || literal == "+inf" || literal == "-inf");
}

static e_scalarType	detectType(const std::string& literal)
{
	if (isCharLiteral(literal))
		return SCALAR_CHAR;
	// Les pseudo-litteraux double (+inf, -inf) finissent par 'f' : les tester avant float.
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

// --- Parsing : string -> valeur scalaire d'origine ---
static char	parseChar(const std::string& literal)
{
	return literal[1];
}

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

// --- Affichage : helpers pour les cas speciaux ---
static bool	isWholeNumber(double value)
{
	double	intPart;

	if (std::isnan(value) || std::isinf(value))
		return false;
	return (std::modf(value, &intPart) == 0.0);
}

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

// --- Affichage des 4 types a partir d'une valeur double intermediaire ---
static void	displayResults(double asDouble)
{
	// --- char ---
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

	// --- int ---
	std::cout << "int: ";
	if (std::isnan(asDouble) || std::isinf(asDouble)
		|| asDouble < static_cast<double>(INT_MIN)
		|| asDouble > static_cast<double>(INT_MAX))
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(asDouble);
	std::cout << std::endl;

	// --- float ---
	std::cout << "float: ";
	printFloatValue(static_cast<float>(asDouble));
	std::cout << std::endl;

	// --- double ---
	std::cout << "double: ";
	printDoubleValue(asDouble);
	std::cout << std::endl;
}

void	ScalarConverter::convert(const std::string& literal)
{
	try
	{
		e_scalarType	type = detectType(literal);

		if (type == SCALAR_CHAR)
		{
			char	c = parseChar(literal);
			// static_cast explicite vers les 3 autres types (exigence du sujet)
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

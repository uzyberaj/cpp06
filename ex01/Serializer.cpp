/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:52:57 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/07/16 16:52:58 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

#include "Data.hpp"

// --- OCF privee : l'utilisateur ne doit jamais creer un Serializer ---
Serializer::Serializer() {}

Serializer::Serializer(const Serializer& other)
{
	(void)other;
}

Serializer& Serializer::operator=(const Serializer& other)
{
	(void)other;
	return *this;
}

Serializer::~Serializer() {}

// Convertit un pointeur Data* en entier non signe (adresse brute en memoire).
// reinterpret_cast : on reinterprete les bits du pointeur comme un nombre.
uintptr_t	Serializer::serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

// Fait l'inverse : on reconvertit l'entier en pointeur Data*.
Data*	Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:52:57 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/10/16 17:19:14 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

#include "Data.hpp"

// On transforme l'adresse d'un objet Data (pointeur)
// en nombre (uintptr_t), puis on refait un pointeur avec ce nombre, sans copier l'objet.
//
// On utilise reinterpret_cast (pas static_cast) : ici on ne convertit pas une "valeur"
// comme 3.14 en int, on garde les memes bits en memoire et on change juste la facon
// de les lire (adresse <-> entier). static_cast ne sert pas a ce genre de truc.
//
// serialize() n'ecrit pas number/name/active dans l'entier : il enregistre seulement
// ou se trouve l'objet. Les donnees restent dans le Data d'origine ; deserialize()
// redonne un pointeur vers ce meme bloc memoire.
//
// Tant que l'objet existe, le pointeur restaure est valide. Si on delete l'objet puis
// on utilise encore l'adresse serializee, c'est invalide (crash possible) : le sujet
// suppose qu'on ne deserialise pas apres destruction.
//
// La classe Serializer existe parce que le sujet l'impose (API + pas d'instanciation).
// Elle ne fait pas de new : pas de fuite liee a Serializer.

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

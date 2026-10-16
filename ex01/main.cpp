/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:52:49 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/10/16 17:16:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>

// Programme de test : on verifie que serialize puis deserialize renvoie le meme
// pointeur et que l'objet Data reste lisible et modifiable

// Affiche le contenu d'un objet Data pour verifier qu'il reste utilisable.
static void	printData(const Data& data, const std::string& label)
{
	std::cout << label << std::endl;
	std::cout << "  number = " << data.number << std::endl;
	std::cout << "  name   = " << data.name << std::endl;
	std::cout << "  active = " << (data.active ? "true" : "false") << std::endl;
}

int	main()
{
	// === Test 1 : serialize puis deserialize — egalite des pointeurs ===
	// Sujet : serialize(&data) puis deserialize(raw) doit renvoyer le meme pointeur.
	// Attendu : original == restored (comparaison de pointeurs).
	std::cout << "=== Test 1 : egalite des pointeurs apres round-trip ===" << std::endl;
	Data	original;
	original.number = 42;
	original.name = "Alice";
	original.active = true;

	Data*		restored = Serializer::deserialize(Serializer::serialize(&original));

	if (restored == &original)
		std::cout << "OK : le pointeur deserialize est identique a l'original" << std::endl;
	else
		std::cout << "ERREUR : pointeurs differents" << std::endl;
	std::cout << std::endl;

	// === Test 2 : structure utilisable apres deserialization ===
	// Sujet : la struct Data doit rester exploitable (lire ses membres).
	// Attendu : les valeurs affichees correspondent a l'objet d'origine.
	std::cout << "=== Test 2 : Data utilisable apres deserialization ===" << std::endl;
	printData(*restored, "Contenu lu via le pointeur restaure :");
	std::cout << std::endl;

	// === Test 3 : modification via le pointeur restaure visible sur l'original ===
	// Sujet : c'est le meme objet en memoire, pas une copie.
	// Attendu : original.name mis a jour apres ecriture via restored.
	std::cout << "=== Test 3 : meme objet en memoire (pas une copie) ===" << std::endl;
	restored->number = 100;
	restored->name = "Bob";
	restored->active = false;

	std::cout << "Apres modification via restored :" << std::endl;
	printData(original, "  original :");
	if (original.number == 100 && original.name == "Bob" && original.active == false)
		std::cout << "OK : original modifie via le pointeur deserialize" << std::endl;
	else
		std::cout << "ERREUR : les donnees de original n'ont pas change" << std::endl;
	std::cout << std::endl;

	// === Test 4 : deux objets distincts → adresses serializees differentes ===
	// Sujet : chaque pointeur a sa propre adresse en memoire.
	// Attendu : raw1 != raw2 et chaque deserialize renvoie le bon objet.
	std::cout << "=== Test 4 : deux objets Data distincts ===" << std::endl;
	Data	first;
	first.number = 1;
	first.name = "First";
	first.active = true;

	Data	second;
	second.number = 2;
	second.name = "Second";
	second.active = false;

	uintptr_t	raw1 = Serializer::serialize(&first);
	uintptr_t	raw2 = Serializer::serialize(&second);

	Data*		ptr1 = Serializer::deserialize(raw1);
	Data*		ptr2 = Serializer::deserialize(raw2);

	if (raw1 != raw2)
		std::cout << "OK : adresses serializees differentes" << std::endl;
	else
		std::cout << "ERREUR : adresses serializees identiques" << std::endl;

	if (ptr1 == &first && ptr2 == &second && ptr1 != ptr2)
		std::cout << "OK : chaque deserialize renvoie le bon objet" << std::endl;
	else
		std::cout << "ERREUR : mauvais pointeurs apres deserialization" << std::endl;
	std::cout << std::endl;

	// === Test 5 : objet alloue sur la heap (new/delete) ===
	// Sujet : le mecanisme doit fonctionner aussi avec un pointeur heap.
	// Attendu : egalite des pointeurs + donnees lisibles, sans fuite memoire.
	std::cout << "=== Test 5 : Data sur la heap (new/delete) ===" << std::endl;
	Data*		heap = new Data();
	heap->number = 7;
	heap->name = "Heap";
	heap->active = true;

	Data*		fromHeap = Serializer::deserialize(Serializer::serialize(heap));

	if (fromHeap == heap)
		std::cout << "OK : pointeur heap restaure correctement" << std::endl;
	else
		std::cout << "ERREUR : pointeur heap incorrect" << std::endl;

	printData(*fromHeap, "Contenu lu via fromHeap :");
	delete heap;
	std::cout << "OK : delete effectue sans crash" << std::endl;
	std::cout << std::endl;

	// === Test 6 : pointeur NULL ===
	// Cas limite : serialiser NULL doit renvoyer 0, deserialiser 0 → NULL.
	std::cout << "=== Test 6 : pointeur NULL ===" << std::endl;
	uintptr_t	rawNull = Serializer::serialize(static_cast<Data*>(0));
	Data*		nullPtr = Serializer::deserialize(rawNull);

	if (rawNull == 0 && nullPtr == 0)
		std::cout << "OK : NULL serialize puis deserialize correctement" << std::endl;
	else
		std::cout << "ERREUR : gestion de NULL incorrecte" << std::endl;

	return 0;
}

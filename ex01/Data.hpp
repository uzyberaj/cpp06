/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:52:45 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/07/16 16:52:46 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

# include <string>

// Structure non vide demandee par le sujet : elle contient de vrais champs.
// On peut lire/modifier ces donnees via un pointeur Data* apres deserialization.
struct Data
{
	int			number;
	std::string	name;
	bool		active;
};

#endif

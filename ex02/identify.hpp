/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:53:30 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/07/16 16:53:31 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFY_HPP
# define IDENTIFY_HPP

class Base;

// generate() cree aleatoirement un A, B ou C et renvoie un Base*.
Base*	generate(void);

// identify() affiche le vrai type ("A", "B" ou "C") via dynamic_cast.
void	identify(Base* p);
void	identify(Base& p);

#endif

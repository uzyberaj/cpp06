/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:53:16 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/10/16 17:32:13 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

// Classe de base polymorphe : seul un destructeur virtuel public est requis.
// Le virtual permet a dynamic_cast de retrouver le vrai type (A, B ou C).

// Sans virtual sur ~Base(), si on fait :
// Base* p = new A();
// delete p;

// le destructeur de A ne serait pas toujours appelé correctement > leaks / comportement faux.
// Avec virtual ~Base(), delete sur un Base* qui pointe vers un A appelle le bon destructeur.

class Base
{
public:
	virtual ~Base();
};

#endif

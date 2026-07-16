/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:53:16 by ulyssezyber       #+#    #+#             */
/*   Updated: 2026/07/16 16:53:17 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

// Classe de base polymorphe : seul un destructeur virtuel public est requis.
// Le virtual permet a dynamic_cast de retrouver le vrai type (A, B ou C).
class Base
{
public:
	virtual ~Base();
};

#endif

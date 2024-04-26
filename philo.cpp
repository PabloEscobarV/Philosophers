/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:09 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/26 14:44:33 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

Alkash::Alkash(long _buchat) : buchat(_buchat)
{

}

Alkash::Alkash(const Alkash& obj)
{
	buchat = obj.buchat;
}

Alkash::~Alkash()
{

}

Alkash&	Alkash::operator=(const Alkash& obj)
{
    if (this == &obj)
        return (*this);
	buchat = obj.buchat;
    return (*this);
}

void	Alkash::getBuchlo(Buchlo& buchlo, mutex& mt)
{
	mt.lock();

	mt.unlock();
}

Buchlo::Buchlo() :
    id(0)
{

}

Buchlo::Buchlo(const Buchlo& obj)
{
    id = obj.id;
}

Buchlo::~Buchlo()
{

}

Buchlo&	Buchlo::operator=(const Buchlo& obj)
{
    if (this == &obj)
        return (*this);
    id = obj.id;
    return (*this);
}

void	Buchlo::set_id(int _id)
{
	id = _id;
}

int		Buchlo::get_id()
{
	return (id);
}

ostream&	operator<<(ostream& os, const Buchlo& obj)
{
	os << "BUCHLO ID:\t" << obj.id << endl;
	return (os);
}
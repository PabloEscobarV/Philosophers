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
    this_thread::sleep_for(chrono::milliseconds(7000));
    cout << "ALKASH HAS BEEN STARTED\n";
	mt.lock();
    cout << buchlo;
    cout << "ALKASH ID:\t" << hex << this_thread::get_id() << endl;
    cout << "--------------------\n";
    this_thread::sleep_for(chrono::milliseconds(3000));
	mt.unlock();
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "ALKASH FINISHED\n";
}

Buchlo::Buchlo() : id(this_thread::get_id())
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

void	Buchlo::set_id(thread::id _id)
{
	id = _id;
}

long		Buchlo::get_id()
{
    return (static_cast<long>(hash<thread::id>{}(id)));
}

ostream&	operator<<(ostream& os, const Buchlo& obj)
{
	os << "BUCHLO ID:\t" << hex << this_thread::get_id() << endl;
	return (os);
}
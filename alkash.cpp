/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/04/29 15:30:36 by blackrider       ###   ########.fr       */
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
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "ALKASH HAS BEEN STARTED\n";
	buchlo.lock();
    cout << buchlo;
    cout << "ALKASH ID:\t" << hex << this_thread::get_id() << endl;
    cout << "--------------------\n";
    this_thread::sleep_for(chrono::milliseconds(1000));
	buchlo.unlock();
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "ALKASH FINISHED\n";
}

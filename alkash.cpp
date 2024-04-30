/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/04/30 10:49:06 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

Alkash::Alkash(long buchat, long find, long sleep) :
    buchat_t(buchat),
    find_t(find),
    sleep_t(sleep)
{

}

Alkash::Alkash(const Alkash& obj)
{
	buchat_t = obj.buchat_t;
    find_t = obj.find_t;
    sleep_t = obj.sleep_t;
}

Alkash::~Alkash()
{

}

Alkash&	Alkash::operator=(const Alkash& obj)
{
    if (this == &obj)
        return (*this);
    buchat_t = obj.buchat_t;
    find_t = obj.find_t;
    sleep_t = obj.sleep_t;
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

void    Alkash::buchat(Buchlo& buchlo, long t)
{
    int     i;

    buchlo.lock();
    timer.start();
    i = 0;
    while (timer.gettime() < t);
    // {
    //     if (!(i % 1000) && i)
    //         cout << timer << endl;
    //     ++i;
    // }
    // this_thread::sleep_for(chrono::milliseconds(t));
    buchlo.unlock();
}
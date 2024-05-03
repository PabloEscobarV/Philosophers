/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/03 12:45:15 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

using namespace alkashi_sim;

Alkash::Alkash(int id_, long buchat, long sleep, long die) :
	id(id_),
    buchat_t(buchat),
    sleep_t(sleep),
    die_t(die),
    time_exec(0),
    metrics(1000)
{
	timer.start();
}

Alkash::Alkash(const Alkash& obj)
{
	buchat_t = obj.buchat_t;
    sleep_t = obj.sleep_t;
    die_t = obj.die_t;
    metrics = obj.metrics;
    id = obj.id;
    time_exec = obj.time_exec;
}

Alkash::~Alkash()
{

}

Alkash&	Alkash::operator=(const Alkash& obj)
{
    if (this == &obj)
        return (*this);
    buchat_t = obj.buchat_t;
    sleep_t = obj.sleep_t;
    die_t = obj.die_t;
    metrics = obj.metrics;
    id = obj.id;
    time_exec = obj.time_exec;
    return (*this);
}

void	Alkash::setmetrics(long m)
{
	metrics = m;
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

void    Alkash::buchat(Buchlo& buchlo, mutex& mt, long t)
{
	if (!t)
        t = buchat_t;
    buchlo.lock();
    cout << timer.gettime() << "[ms]:\t" << id << "\thas taken a fork\n";
    this_thread::sleep_for(chrono::milliseconds(t));
    buchlo.unlock();
}

void	Alkash::finding(mutex& mt)
{
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\tis finding buchlo" << endl;
	mt.unlock();
}

void	Alkash::sleep(mutex& mt, long t)
{
    if (!t)
        t = sleep_t;
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\tis sleepnig" << endl;
	mt.unlock();
    this_thread::sleep_for(chrono::milliseconds(t));
}

long    Alkash::getdie()
{
    return (die_t);
}

long    Alkash::gebuchat()
{
    return (buchat_t);
}

long    Alkash::getsleep()
{
    return (sleep_t);
}

int     Alkash::get_id()
{
    return (id);
}

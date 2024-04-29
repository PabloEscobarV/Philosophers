/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:09 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/29 15:28:48 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

Timer::Timer(bool t)
{
    if (t)
        timer_start = chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    // timer_stop = chrono::high_resolution_clock::now();
    // dur = timer_stop - timer_start;
    // cout << "DURATION:\t" << dur.count() << "\tSECONDS" << endl;
}

void    Timer::start()
{
    timer_start = chrono::high_resolution_clock::now();
}

void	Timer::stop()
{
	timer_stop = chrono::high_resolution_clock::now();
    dur = timer_stop - timer_start;
}

ostream&	operator<<(ostream& os, const Timer& t)
{
	os << "DURATION:\t" << t.dur.count() << "\tSECONDS";
	return (os);
}

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

void    Buchlo::lock()
{
    mt.lock();
}

void	Buchlo::unlock()
{
	mt.unlock();
}
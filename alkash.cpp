/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/04/30 12:49:42 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

Alkash::Alkash(int id_, long buchat, long find, long sleep) :
	id(id_),
    buchat_t(buchat),
    find_t(find),
    sleep_t(sleep),
    time_exec(0),
    metrics(1000)
{
	timer.start();
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

void    Alkash::buchat(Buchlo& buchlo, long t)
{
	if (!t)
		t = buchat_t;
    buchlo.lock();
    time_exec += t;
	mt.lock();
    cout << time_exec + timer.gettime() << "[ms]:\t" << id << "\thas taken a fork\n";
	mt.unlock();
    this_thread::sleep_for(chrono::milliseconds(t));
    buchlo.unlock();
	finding();
}

void	Alkash::finding(long t)
{
	mt.lock();
	this_thread::sleep_for(chrono::milliseconds(1000));
	// time_exec += t;
	cout << time_exec + timer.gettime() << "[ms]:\t" << id << "\tis finding buchlo" << endl;
	mt.unlock();
}

void	Alkash::sleep(long t)
{
	
}
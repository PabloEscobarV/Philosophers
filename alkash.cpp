/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/03 15:02:59 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

namespace alkashi_sim
{
	Alkash::Alkash(int id_, long buchat, long sleep, long die) :
		id(id_),
		buchat_t(buchat),
		sleep_t(sleep),
		die_t(die),
		time_exec(0),
		metrics(1000),
		buchat_permit(false)
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

	void	Alkash::getBuchlo(Buchlo& buchlo, Buchlo& zapyvon)
	{
		buchlo.lock();
		zapyvon.lock();
		this->buchlo = &buchlo;
		this->zapyvon = &zapyvon;
		buchat_permit = true;
	}

	void    Alkash::buchat(mutex& mt, long t)
	{
		if (!buchat_permit)
			return ;
		if (!t)
			t = buchat_t;
		cout << timer.gettime() << "[ms]:\t" << id << "\thas taken a fork\n";
		this_thread::sleep_for(chrono::milliseconds(t));
		buchlo->unlock();
		zapyvon->unlock();
		buchat_permit = false;
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/09 14:51:39 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/alkash.h"

namespace alkashi_sim
{
Alkash::Alkash(int id_, long buchat, long sleep, long die) :
	id(id_),
	buchat_tm(buchat),
	sleep_tm(sleep),
	die_tm(die),
	time_exec(0),
	metrics(1000),
	last_btm(0),
	status(0)
{
	if (die == 0)
		return ;
	timer.start();
	setbit(status, LIFE_STATE);
	if (!(id % 2))
		setbit(status, PERMITION_BUCHAT);
	die_mtm = (float)die_tm / metrics;
}

Alkash::Alkash(const Alkash& obj)
{
	buchat_tm = obj.buchat_tm;
	sleep_tm = obj.sleep_tm;
	die_tm = obj.die_tm;
	metrics = obj.metrics;
	id = obj.id;
	time_exec = obj.time_exec;
	last_btm = obj.last_btm;
	status = obj.status;
	die_mtm = obj.die_mtm;
	timer.start();
}

Alkash::~Alkash()
{

}

Alkash&	Alkash::operator=(const Alkash& obj)
{
	if (this == &obj)
		return (*this);
	buchat_tm = obj.buchat_tm;
	sleep_tm = obj.sleep_tm;
	die_tm = obj.die_tm;
	metrics = obj.metrics;
	id = obj.id;
	time_exec = obj.time_exec;
	last_btm = obj.last_btm;
	status = obj.status;
	die_mtm = obj.die_mtm;
	timer.start();
	return (*this);
}

void	Alkash::setmetrics(long m)
{
	metrics = m;
	die_mtm = (float)die_tm / metrics;
}

void	Alkash::getBuchlo(Buchlo& buchlo, Buchlo& zapyvon)
{
	buchlo.lock();
	zapyvon.lock();
	this->buchlo = &buchlo;
	this->zapyvon = &zapyvon;
	// buchat_permit = true;
	setbit(status, IS_LOCKED);
	
}

bool    Alkash::buchat(mutex& mt, t_cv& cv, long t)
{
	if (!getbit(status, IS_LOCKED) || !getbit(status, LIFE_STATE))
		return (false);
	if ((long)(timer.gettime_ms() - last_btm) > die_tm)
	{
		setbit(status, LIFE_STATE, DIE_STATE);
		die_msg(mt, "----------ALKASH is DEAD!!!----------");
		return (false);
	}
	setbit(status, IS_FINDING, false);
	setbit(status, IS_BUCHING);
	if (!t)
		t = buchat_tm;
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\thas taken a fork\n";
	mt.unlock();
	this_thread::sleep_for(chrono::milliseconds(t));
	last_btm = timer.gettime_ms();
	buchlo->unlock(cv);
	zapyvon->unlock(cv);
	setbit(status, IS_LOCKED, false);
	return (true);
}

bool    Alkash::buchat(mutex& mt, long t)
{
	if (!getbit(status, IS_LOCKED) || !getbit(status, LIFE_STATE))
		return (false);
	if ((long)(timer.gettime_ms() - last_btm) > die_tm)
	{
		setbit(status, LIFE_STATE, DIE_STATE);
		die_msg(mt, "----------ALKASH is DEAD!!!----------");
		return (false);
	}
	setbit(status, IS_FINDING, false);
	setbit(status, IS_BUCHING);
	if (!t)
		t = buchat_tm;
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\thas taken a fork\n";
	mt.unlock();
	this_thread::sleep_for(chrono::milliseconds(t));
	last_btm = timer.gettime_ms();
	buchlo->unlock();
	zapyvon->unlock();
	setbit(status, IS_LOCKED, false);
	return (true);
}

void	Alkash::sleep(mutex& mt, long t)
{
	if (!t)
		t = sleep_tm;
	setbit(status, IS_BUCHING, false);
	setbit(status, IS_SLEEPING);
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\tis sleepnig" << endl;
	mt.unlock();
	this_thread::sleep_for(chrono::milliseconds(t));
}

void	Alkash::finding(mutex& mt)
{
	if (getbit(status, IS_FINDING))
		return ;
	setbit(status, IS_SLEEPING, false);
	setbit(status, IS_FINDING);
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\tis finding buchlo" << endl;
	mt.unlock();
}

long    Alkash::getdie()
{
	return (die_tm);
}

long    Alkash::gebuchat()
{
	return (buchat_tm);
}

long    Alkash::getsleep()
{
	return (sleep_tm);
}

int     Alkash::get_id()
{
	return (id);
}

t_uchar	Alkash::state()
{
	if (!getbit(status, IS_BUCHING) && (timer.gettime_ms() - last_btm) > die_tm)
		setbit(status, LIFE_STATE, DIE_STATE);
	return (status);
}

bool	Alkash::lifestatus()
{
	if (!getbit(status, LIFE_STATE))
		return (false);
	if (!getbit(status, IS_BUCHING) && (timer.gettime_ms() - last_btm) > die_tm)
	{
		setbit(status, LIFE_STATE, DIE_STATE);
		return (false);
	}
	return (true);
}

void	Alkash::die_msg(mutex& mt, const char* msg)
{
	mt.lock();
	cout << "ID[" << id << "]: " << msg << endl;
	mt.unlock();
}

void	setbit(t_uchar& data, t_uchar bit, t_uchar val)
{
	if (bit > 7 || bit < 0)
		bit = 0;
	if (val > 1)
		val = 1;
	if (val)
		data |= (val << bit);
	else
		data &= ~(1 << bit);
}

t_uchar	getbit(t_uchar data, t_uchar bit)
{
	if (bit > 7 || bit < 0)
		return (0);
	return (data & (1 << bit));
}

void	Alkash::setpermition(t_uchar perm)
{
	if (perm)
	{
		setbit(status, PERMITION_BUCHAT);
		return ;
	}
	setbit(status, PERMITION_BUCHAT, false);
}

}

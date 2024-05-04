/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/04 22:50:43 by blackrider       ###   ########.fr       */
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
	bechavior_st(UNDETREMINATE),
	buchat_permit(false),
	die_status(ALIVE_STATE)
{
	timer.start();
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
	bechavior_st = obj.bechavior_st;
	die_mtm = obj.die_mtm;
	die_status = obj.die_status;
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
	bechavior_st = obj.bechavior_st;
	die_mtm = obj.die_mtm;
	die_status = obj.die_status;
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
	buchat_permit = true;
}

bool    Alkash::buchat(mutex& mt, long t)
{
	if (!buchat_permit)
		return (false);
	if (die_status == DIE_STATE)
		return (false);
	if ((timer.gettime_ms() - last_btm) > die_tm)
	{
		die_status = DIE_STATE;
		die_msg(mt, "----------ALKASH is DEAD!!!----------");
		return (false);
	}
	if (!t)
		t = buchat_tm;
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\thas taken a fork\n";
	mt.unlock();
	bechavior_st = IS_BUCHING;
	this_thread::sleep_for(chrono::milliseconds(t));
	last_btm = timer.gettime_ms();
	buchlo->unlock();
	zapyvon->unlock();
	buchat_permit = false;
	return (true);
}

void	Alkash::finding(mutex& mt)
{
	if (bechavior_st == IS_FINDING)
		return ;
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\tis finding buchlo" << endl;
	mt.unlock();
	bechavior_st = IS_FINDING;
}

void	Alkash::sleep(mutex& mt, long t)
{
	if (!t)
		t = sleep_tm;
	mt.lock();
	cout << timer.gettime() << "[ms]:\t" << id << "\tis sleepnig" << endl;
	mt.unlock();
	bechavior_st = IS_SLEEPING;
	this_thread::sleep_for(chrono::milliseconds(t));
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

bool	Alkash::state()
{
	if (die_status == DIE_STATE)
		return (DIE_STATE);
	if ((timer.gettime_ms() - last_btm) > die_tm)
		return (DIE_STATE);
	return (ALIVE_STATE);
}

void	Alkash::die_msg(mutex& mt, const char* msg)
{
	mt.lock();
	cout << "ID[" << id << "]: " << msg << endl;
	mt.unlock();
}

}

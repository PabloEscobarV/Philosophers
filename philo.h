/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:13 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/03 15:02:04 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "timer.h"
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

namespace	alkashi_sim
{

class	Buchlo
{
	bool		status;
	int			id;
	mutex		mt;
public:
	Buchlo(int id = 0);
	Buchlo(const Buchlo& obj);
	~Buchlo();
	Buchlo&	operator=(const Buchlo& obj);
	void	set_id(int _id);
	int		get_id();
	void	lock();
	void	unlock();
	bool	state();
	friend ostream&	operator<<(ostream& os, const Buchlo& obj);
};

class	Alkash
{
	bool			buchat_permit;
	int				id;
	float			time_exec;
	long			sleep_t;
	long			buchat_t;
	long			die_t;
	long			metrics;
	Buchlo*			buchlo;
	Buchlo*			zapyvon;
public:
	Timer<float>	timer;
	Alkash(int id = 0, long buchat = 0, long sleep = 0, long die = 0);
	Alkash(const Alkash& obj);
	~Alkash();
	Alkash&			operator=(const Alkash& obj);
	void			setmetrics(long metrics);
	void			getBuchlo(Buchlo& buchlo, Buchlo& zapyvon);
	void			buchat(mutex& mt, long t = 0);
	void			sleep(mutex& mt, long t = 0);
	void			finding(mutex& mt);
	long			gebuchat();
	long			getsleep();
	long			getdie();
	int				get_id();
};

class	TaskSheduler
{
	int		count;
	int		eating_tms;
	Alkash	*alkasi;
	Buchlo	*buchlo;
	thread	*threads;
	mutex	out_mt;
	mutex	planer_mt;
	int		correcti(int num);
	void	clear_mem();
	void	planing(int num);
	int		checkbuchlo(int num);
public:
	TaskSheduler(int count = 1, long sleep_tm = 0, long eat_tm = 0, long die_tm = 0);
	TaskSheduler(const TaskSheduler& obj);
	~TaskSheduler();
	TaskSheduler&	operator=(const TaskSheduler& obj);
	void			set_ents(int eating_tms = 0);
	void			startsimulation();
};

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:13 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/03 10:40:50 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

class	Buchlo
{
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
	friend ostream&	operator<<(ostream& os, const Buchlo& obj);
};

class	Alkash
{
	int				id;
	float			time_exec;
	long			sleep_t;
	long			buchat_t;
	long			die_t;
	long			metrics;
public:
	Timer<float>	timer;
	Alkash(int id = 0, long buchat = 0, long sleep = 0, long die = 0);
	Alkash(const Alkash& obj);
	~Alkash();
	Alkash&			operator=(const Alkash& obj);
	void			setmetrics(long metrics);
	void			getBuchlo(Buchlo& buchlo, mutex& mt);
	void			buchat(Buchlo& buchlo, mutex& mt, long t = 0);
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
	void	clear_mem();
public:
	TaskSheduler(int count = 0, long sleep_tm = 0, long eat_tm = 0, long die_tm = 0);
	TaskSheduler(const TaskSheduler& obj);
	~TaskSheduler();
	TaskSheduler&	operator=(const TaskSheduler& obj);
	void			set_ents(int eating_tms = 0);
};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasksheduler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:53:53 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/03 13:31:56 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

namespace	alkashi_sim
{

TaskSheduler::TaskSheduler(int cnt, long slp_tm, long eat_tm, long die_tm) :
	count(cnt)
{
	if (count < 1)
	{
		count = 0;
		alkasi = nullptr;
		buchlo = nullptr;
		threads = nullptr;
		return ;
	}
	alkasi = new Alkash[cnt];
	buchlo = new Buchlo[cnt];
	threads = new thread[cnt];
	if (!alkasi || !buchlo || !threads)
	{
		clear_mem();
		throw runtime_error("Memmory allocation error");
	}
	while (--cnt >= 0)
	{
		alkasi[cnt] = Alkash(cnt, eat_tm, slp_tm, die_tm);
		buchlo[cnt] = Buchlo(cnt);
	}
}

TaskSheduler::TaskSheduler(const TaskSheduler& obj)
{
	count = obj.count;
	if (!count)
	{
		alkasi = nullptr;
		buchlo = nullptr;
		threads = nullptr;
		return ;
	}
	alkasi = new Alkash[obj.count];
	buchlo = new Buchlo[obj.count];
	threads = new thread[obj.count];
	if (!alkasi || !buchlo || !threads)
	{
		clear_mem();
		throw runtime_error("Memmory allocation error");
	}
	for (int cnt = 0; cnt < count; ++cnt)
	{
		alkasi[cnt] = Alkash(obj.alkasi[cnt].get_id(), obj.alkasi[cnt].gebuchat(),
			obj.alkasi[cnt].getsleep(), obj.alkasi[cnt].getdie());
		buchlo[cnt] = Buchlo(cnt);
	}
}

TaskSheduler&   TaskSheduler::operator=(const TaskSheduler& obj)
{
	if (this == &obj)
		return (*this);
	clear_mem();
	count = obj.count;
	if (!count)
		return (*this);
	alkasi = new Alkash[obj.count];
	buchlo = new Buchlo[obj.count];
	threads = new thread[obj.count];
	if (!alkasi || !buchlo)
	{
		clear_mem();
		throw runtime_error("Memmory allocation error");
	}
	for (int cnt = 0; cnt < count; ++cnt)
	{
		alkasi[cnt] = Alkash(obj.alkasi[cnt].get_id(), obj.alkasi[cnt].gebuchat(),
			obj.alkasi[cnt].getsleep(), obj.alkasi[cnt].getdie());
		buchlo[cnt] = Buchlo(cnt);
	}
	return (*this);
}

TaskSheduler::~TaskSheduler()
{
	clear_mem();
}

void	TaskSheduler::clear_mem()
{
	delete[] alkasi;
	delete[] buchlo;
	delete[] threads;
	alkasi = nullptr;
	buchlo = nullptr;
	threads = nullptr;
}

void	TaskSheduler::set_ents(int tmp)
{
	eating_tms = tmp;
}

void	TaskSheduler::planing()
{
	out_mt.lock();
	cout << "Thread ID: " << hex << this_thread::get_id() << endl; 
	out_mt.unlock();
}

void	TaskSheduler::startsimulation()
{
	cout << "Simulation has started\n";
	if (count < 1)
	{
		cout << "Bad parameters!!!!\n";
		return ;
	}
	for (int i = 0; i < count; ++i)
		threads[i] = thread(&TaskSheduler::planing, this);
	for (int i = 0; i < count; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	cout << "Simulation has finished\n";
}

}

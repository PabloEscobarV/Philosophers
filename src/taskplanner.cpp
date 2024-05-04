/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:53:53 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/04 13:31:05 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/taskplanner.h"

namespace	alkashi_sim
{

TaskPlanner::TaskPlanner(int cnt, long slp_tm, long eat_tm, long die_tm) :
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

TaskPlanner::TaskPlanner(const TaskPlanner& obj)
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

TaskPlanner&   TaskPlanner::operator=(const TaskPlanner& obj)
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

TaskPlanner::~TaskPlanner()
{
	clear_mem();
}

void	TaskPlanner::clear_mem()
{
	delete[] alkasi;
	delete[] buchlo;
	delete[] threads;
	alkasi = nullptr;
	buchlo = nullptr;
	threads = nullptr;
}

void	TaskPlanner::set_ents(int tmp)
{
	eating_tms = tmp;
}

inline int	TaskPlanner::correcti(int num)
{
	if (num > count - 2)
		return (0);
	return (num + 1);
}

inline int	TaskPlanner::checkbuchlo(int num)
{
	if (buchlo[num].state() && buchlo[correcti(num)].state())
		return (1);
	return (0);
}

void	TaskPlanner::planing(int num)
{
	// while ()
	// {
		// out_mt.lock();
		// cout << "Thread ID[" << num << "]: " << hex << this_thread::get_id() << endl; 
		// cout << "Alkash ID: " << alkasi[num].get_id() << endl;
		// out_mt.unlock();
		planer_mt.lock();
		if (checkbuchlo(num))
			alkasi[num].getBuchlo(buchlo[num], buchlo[correcti(num)]);
		planer_mt.unlock();
		if (alkasi[num].buchat(out_mt))
			alkasi[num].sleep(out_mt);
		alkasi[num].finding(out_mt);
	// }
}

void	TaskPlanner::startsimulation()
{
	cout << "Simulation has started\n";
	if (count < 1)
	{
		cout << "Bad parameters!!!!\n";
		return ;
	}
	for (int i = 0; i < count; ++i)
		threads[i] = thread(&TaskPlanner::planing, this, i);
	for (int i = 0; i < count; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	cout << "Simulation has finished\n";
}

}

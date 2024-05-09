/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:53:53 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/09 13:52:45 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/taskplanner.h"

namespace	alkashi_sim
{

TaskPlanner::TaskPlanner(int cnt, long slp_tm, long eat_tm, long die_tm) :
	count(cnt),
	lastcheck(0),
	status(0),
	minchecktime(500),
	insp_frequency(1000)
{
	timer.start();
	setbit(status, LIFE_STATE);
	if (count < 1)
	{
		count = 0;
		alkashi = nullptr;
		buchlo = nullptr;
		threads = nullptr;
		return ;
	}
	alkashi = new Alkash[cnt];
	buchlo = new Buchlo[cnt];
	threads = new thread[cnt];
	if (!alkashi || !buchlo || !threads)
	{
		clear_mem();
		throw runtime_error("Memmory allocation error");
	}
	while (--cnt >= 0)
	{
		alkashi[cnt] = Alkash(cnt, eat_tm, slp_tm, die_tm);
		buchlo[cnt] = Buchlo(cnt);
	}
	if (count % 2)
		alkashi[count - 1].setpermition(false);
	for (int i = 0; i < count; ++i)
		cout << "ID[" << i << "]: STATUS: " << (int)alkashi[i].state() << endl;
}

TaskPlanner::TaskPlanner(const TaskPlanner& obj)
{
	count = obj.count;
	lastcheck = obj.lastcheck;
	minchecktime = obj.minchecktime;
	status = obj.status;
	insp_frequency = obj.insp_frequency;
	if (!count)
	{
		alkashi = nullptr;
		buchlo = nullptr;
		threads = nullptr;
		return ;
	}
	alkashi = new Alkash[obj.count];
	buchlo = new Buchlo[obj.count];
	threads = new thread[obj.count];
	if (!alkashi || !buchlo || !threads)
	{
		clear_mem();
		throw runtime_error("Memmory allocation error");
	}
	for (int cnt = 0; cnt < count; ++cnt)
	{
		alkashi[cnt] = Alkash(obj.alkashi[cnt].get_id(), obj.alkashi[cnt].gebuchat(),
			obj.alkashi[cnt].getsleep(), obj.alkashi[cnt].getdie());
		buchlo[cnt] = Buchlo(cnt);
	}
}

TaskPlanner&   TaskPlanner::operator=(const TaskPlanner& obj)
{
	if (this == &obj)
		return (*this);
	clear_mem();
	lastcheck = obj.lastcheck;
	count = obj.count;
	minchecktime = obj.minchecktime;
	status = obj.status;
	insp_frequency = obj.insp_frequency;
	if (!count)
		return (*this);
	alkashi = new Alkash[obj.count];
	buchlo = new Buchlo[obj.count];
	threads = new thread[obj.count];
	if (!alkashi || !buchlo)
	{
		clear_mem();
		throw runtime_error("Memmory allocation error");
	}
	for (int cnt = 0; cnt < count; ++cnt)
	{
		alkashi[cnt] = Alkash(obj.alkashi[cnt].get_id(), obj.alkashi[cnt].gebuchat(),
			obj.alkashi[cnt].getsleep(), obj.alkashi[cnt].getdie());
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
	delete[] alkashi;
	delete[] buchlo;
	delete[] threads;
	alkashi = nullptr;
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

t_uchar	TaskPlanner::checkbuchlo(int num)
{
	if (!getbit(alkashi[num].state(), PERMITION_BUCHAT))
		return (0);
	if (buchlo[num].state() && buchlo[correcti(num)].state())
		return (1);
	return (0);
}

t_uchar	TaskPlanner::checkpermition(int num)
{
	unique_lock<mutex>	lock(planer_mt);

	cv.wait(lock, [&]
	{
		if (getbit(alkashi[num].state(), PERMITION_BUCHAT)
			|| getbit(status, LIFE_STATE) == DIE_STATE)
			// if (buchlo[num].state() && buchlo[correcti(num)].state())
				return (true);
		return (false);
	});
	return (true);
}

t_uchar	TaskPlanner::checkabpility(int num)
{
	if (buchlo[num].state() && buchlo[correcti(num)].state())
		return (true);
	return (false);
}

void	TaskPlanner::checkalkashi()
{
	while (getbit(status, LIFE_STATE) != DIE_STATE)
	{
		this_thread::sleep_for(chrono::milliseconds(insp_frequency));
		out_mt.lock();
		cout << "----------------CHECK TIME---------------" << endl;
		out_mt.unlock();
		for (int i = 0; i < count; ++i)
			if (getbit(alkashi[i].lifestatus()) == DIE_STATE)
			{
				setbit(status, LIFE_STATE, DIE_STATE);
				alkashi[i].die_msg(out_mt, "ALKASH is DEAD!!!");
				// return ;	
			}
		if (timer.gettime() > 10.0)
		{
			setbit(status, LIFE_STATE, DIE_STATE);
			return ;
		}
	}
}

bool	TaskPlanner::checkalkashi(const int& num)
{
	if (getbit(status, LIFE_STATE) == DIE_STATE)
		return (DIE_STATE);
	if (long(1000 * (timer.gettime() - lastcheck)) < insp_frequency)
		return (ALIVE_STATE);
	lastcheck_mt.lock();
	if (long(1000 * (timer.gettime() - lastcheck)) < insp_frequency)
	{
		lastcheck_mt.unlock();
		return (ALIVE_STATE);
	}
	lastcheck = timer.gettime();
	lastcheck_mt.unlock();
	out_mt.lock();
	cout << "----------------CHECK TIME---------------" << endl;
	out_mt.unlock();
	for (int i = 0; i < count; ++i)
		if (alkashi[i].lifestatus() == DIE_STATE)
		{
			setbit(status, LIFE_STATE, DIE_STATE);
			alkashi[i].die_msg(out_mt, "ALKASH is DEAD!!!");
			planer_mt.lock();
			cv.notify_all();
			planer_mt.unlock();
			// return (DIE_STATE);	
		}
	if (timer.gettime() > 10.0 || getbit(status, LIFE_STATE) == DIE_STATE)
	{
		setbit(status, LIFE_STATE, DIE_STATE);
		return (DIE_STATE);
	}
	return (ALIVE_STATE);
}

void	TaskPlanner::planing(int num)
{
	while (checkalkashi(num))
	{
		planer_mt.lock();
		if (checkbuchlo(num))
			alkashi[num].getBuchlo(buchlo[num], buchlo[correcti(num)]);
		planer_mt.unlock();
		if (alkashi[num].buchat(out_mt))
		{
			planer_mt.lock();
			alkashi[num].setpermition(false);
			alkashi[correcti(num)].setpermition();
			planer_mt.unlock();
			alkashi[num].sleep(out_mt);
			alkashi[num].finding(out_mt);
		}
	}
}

void	TaskPlanner::zapoj(int num)
{
	while (getbit(status, LIFE_STATE) != DIE_STATE)
	{
		planer_mt.lock();
		if (checkbuchlo(num))
			alkashi[num].getBuchlo(buchlo[num], buchlo[correcti(num)]);
		planer_mt.unlock();
		if (alkashi[num].buchat(out_mt))
		{
			planer_mt.lock();
			alkashi[num].setpermition(false);
			alkashi[correcti(num)].setpermition();
			planer_mt.unlock();
			alkashi[num].sleep(out_mt);
			alkashi[num].finding(out_mt);
		}
	}
}

void	TaskPlanner::planner(int num)
{
	while (checkalkashi(num))
	{
		checkpermition(num);
		planer_mt.lock();
		if (!buchlo[num].state() && buchlo[correcti(num)].state())
		{
			planer_mt.unlock();
			continue ;
		}
		alkashi[num].getBuchlo(buchlo[num], buchlo[correcti(num)]);
		planer_mt.unlock();
		if (alkashi[num].buchat(out_mt))
		{
			planer_mt.lock();
			alkashi[num].setpermition(false);
			alkashi[correcti(num)].setpermition();
			cv.notify_all();
			planer_mt.unlock();
			alkashi[num].sleep(out_mt);
			alkashi[num].finding(out_mt);
		}
	}
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

void	TaskPlanner::startsimplanner()
{
	cout << "Simulation has started\n";
	if (count < 1)
	{
		cout << "Bad parameters!!!!\n";
		return ;
	}
	for (int i = 0; i < count; ++i)
		threads[i] = thread(&TaskPlanner::zapoj, this, i);
	checkalkashi();
	for (int i = 0; i < count; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	cout << "Simulation has finished\n";
}

void	TaskPlanner::startplanner()
{
	cout << "Simulation has started\n";
	if (count < 1)
	{
		cout << "Bad parameters!!!!\n";
		return ;
	}
	for (int i = 0; i < count; ++i)
		threads[i] = thread(&TaskPlanner::planner, this, i);
	for (int i = 0; i < count; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	cout << "Simulation has finished\n";
}

}

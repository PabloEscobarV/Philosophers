/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasksheduler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:53:53 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/03 10:41:21 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

TaskSheduler::TaskSheduler(int cnt, long slp_tm, long eat_tm, long die_tm) :
    count(cnt)
{
    alkasi = new Alkash[cnt];
    buchlo = new Buchlo[cnt];

    if (!alkasi || !buchlo)
    {
        delete[] alkasi;
        delete[] buchlo;
        alkasi = nullptr;
        buchlo = nullptr;
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
	}
    alkasi = new Alkash[obj.count];
    buchlo = new Buchlo[obj.count];
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
	alkasi = nullptr;
	buchlo = nullptr;
}

void	TaskSheduler::set_ents(int tmp)
{
	eating_tms = tmp;
}
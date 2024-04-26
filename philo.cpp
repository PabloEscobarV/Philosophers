/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:07:38 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/25 13:30:00 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <iostream>
#include <thread>

using namespace std;

Alkash::Alkash(int die, int buchat, int sleep, int finding) :
    t_die(die),
    t_buchat(buchat),
    t_sleep(sleep),
    t_finding(finding),
    timer(0)
{
    
}

Alkash::Alkash(const Alkash& obj)
{
    if (this == &obj)
        return ;
    t_die = obj.t_die;
    t_buchat = obj.t_buchat;
    t_sleep = obj.t_sleep;
    t_finding = obj.t_finding;
    timer = obj.timer;
}

Alkash&	Alkash::operator=(const Alkash& obj)
{
    if (this == &obj)
        return ;
    t_die = obj.t_die;
    t_buchat = obj.t_buchat;
    t_sleep = obj.t_sleep;
    t_finding = obj.t_finding;
    timer = obj.timer;
}

void	Alkash::buchat(long buchat)
{
    if (buchat < 0)
        buchat = t_buchat;
    timer = buchat;
}

void	Alkash::sleep(long sleep)
{
    if (sleep < 0)
        sleep = t_sleep;
    timer = sleep;
    this_thread::sleep_for(chrono::milliseconds(sleep));
}

void	Alkash::finding(long finding)
{
    if (!finding)
        finding = t_finding;
	timer = finding;
}

long	Alkash::checktime()
{
	end = P_Clock::now();
	duration = std::chrono::duration_cast<P_Duration>(end - start);
	timer = duration.count();
	return (timer);
}
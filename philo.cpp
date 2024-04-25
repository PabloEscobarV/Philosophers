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

Alkash::Alkash(int ttd, int tte, int tts, int ttt) :
    t_td(ttd),
    t_te(tte),
    t_ts(tts),
    t_tt(ttt),
    timer(0)
{
    
}

Alkash::Alkash(const Alkash& obj)
{
    if (this == &obj)
        return ;
    t_td = obj.t_td;
    t_te = obj.t_te;
    t_ts = obj.t_ts;
    t_tt = obj.t_ts;
    timer = obj.timer;
}

Alkash&	Alkash::operator=(const Alkash& obj)
{
    if (this == &obj)
        return ;
    t_td = obj.t_td;
    t_te = obj.t_te;
    t_ts = obj.t_ts;
    t_tt = obj.t_ts;
    timer = obj.timer;
}

void	Alkash::eat()
{

}

void	Alkash::sleep()
{
	
}

void	Alkash::think()
{
	
}
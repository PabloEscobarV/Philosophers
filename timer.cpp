/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:59:27 by blackrider        #+#    #+#             */
/*   Updated: 2024/04/29 15:29:53 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

Timer::Timer(bool t)
{
    if (t)
        timer_start = chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    // timer_stop = chrono::high_resolution_clock::now();
    // dur = timer_stop - timer_start;
    // cout << "DURATION:\t" << dur.count() << "\tSECONDS" << endl;
}

void    Timer::start()
{
    timer_start = chrono::high_resolution_clock::now();
}

void	Timer::stop()
{
	timer_stop = chrono::high_resolution_clock::now();
    dur = timer_stop - timer_start;
}

ostream&	operator<<(ostream& os, const Timer& t)
{
	os << "DURATION:\t" << t.dur.count() << "\tSECONDS";
	return (os);
}

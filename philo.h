/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:13 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/30 10:23:32 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

class	Buchlo
{
	mutex	mt;
	thread::id	id;
public:
	Buchlo();
	Buchlo(const Buchlo& obj);
	~Buchlo();
	Buchlo&	operator=(const Buchlo& obj);
	void	set_id(thread::id _id);
	long	get_id();
	void	lock();
	void	unlock();
	friend ostream&	operator<<(ostream& os, const Buchlo& obj);
};

class	Alkash : public thread
{
	long			sleep_t;
	long			find_t;
	long			buchat_t;
public:
	Timer<float>	timer;
	Alkash(long buchat = 0, long find = 0, long sleep = 0);
	Alkash(const Alkash& obj);
	~Alkash();
	Alkash&			operator=(const Alkash& obj);
	void			getBuchlo(Buchlo& buchlo, mutex& mt);
	void			buchat(Buchlo& buchlo, long t);
	// void			sleep(long t);
	// void			finding(long t);
};


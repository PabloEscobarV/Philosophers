/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:13 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/30 12:41:11 by polenyc          ###   ########.fr       */
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
	int				id;
	float			time_exec;
	long			sleep_t;
	long			find_t;
	long			buchat_t;
	long			metrics;
	mutex			mt;
public:
	Timer<float>	timer;
	Alkash(int id = 0, long buchat = 0, long find = 0, long sleep = 0);
	Alkash(const Alkash& obj);
	~Alkash();
	Alkash&			operator=(const Alkash& obj);
	void			setmetrics(long metrics);
	void			getBuchlo(Buchlo& buchlo, mutex& mt);
	void			buchat(Buchlo& buchlo, long t = 0);
	void			sleep(long t = 0);
	void			finding(long t = 0);
};


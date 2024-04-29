/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:13 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/29 15:26:25 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

class	Timer
{
	chrono::high_resolution_clock::time_point	timer_start;
	chrono::high_resolution_clock::time_point	timer_stop;
	chrono::duration<double> dur;
public:
	Timer(bool t = false);
	~Timer();
	void	start();
	void	stop();
	friend ostream&	operator<<(ostream& os, const Timer& t);
};

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
	long	buchat;
public:
	Alkash(long _buchat = 0);
	Alkash(const Alkash& obj);
	~Alkash();
	Alkash&	operator=(const Alkash& obj);
	void	getBuchlo(Buchlo& buchlo, mutex& mt);
};
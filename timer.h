/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:10:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/03 13:16:06 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <chrono>

using namespace std;

namespace	alkashi_sim
{

	template<typename T>
	class	Timer
	{
		chrono::high_resolution_clock::time_point	timer_start;
		chrono::high_resolution_clock::time_point	timer_stop;
		chrono::duration<T> dur;
	public:
		Timer(bool t = false);
		~Timer();
		void	start();
		void	stop();
		T		gettime() const;
		template <typename F_T>
		friend ostream&	operator<<(ostream& os, const Timer<F_T>& t);
	};

	template<typename T>
	Timer<T>::Timer(bool t)
	{
		// if (t)
		//     timer_start = chrono::high_resolution_clock::now();
	}

	template<typename T>
	Timer<T>::~Timer()
	{
		// timer_stop = chrono::high_resolution_clock::now();
		// dur = timer_stop - timer_start;
		// cout << "DURATION:\t" << dur.count() << "\tSECONDS" << endl;
	}

	template<typename T>
	void    Timer<T>::start()
	{
		timer_start = chrono::high_resolution_clock::now();
	}

	template<typename T>
	void	Timer<T>::stop()
	{
		timer_stop = chrono::high_resolution_clock::now();
		dur = timer_stop - timer_start;
	}

	template<typename T>
	T       Timer<T>::gettime() const
	{
		return (chrono::duration<T>(chrono::high_resolution_clock::now() - timer_start).count());
	}

	template<typename T>
	ostream&	operator<<(ostream& os, const Timer<T>& t)
	{
		os << "DURATION:\t" << t.gettime() << "\tSECONDS";
		return (os);
	}

}

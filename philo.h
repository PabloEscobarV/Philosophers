/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:02 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/25 13:37:50 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <thread>
#include <chrono>

using namespace std;

using P_Clock = chrono::high_resolution_clock;
using P_Duration = chrono::milliseconds;

class	Alkash
{
	long								t_die;
	long								t_buchat;
	long								t_sleep;
	long								t_finding;
	long								timer;
	P_Duration							duration;
	std::chrono::time_point<P_Clock>	start;
	std::chrono::time_point<P_Clock>	end;
public:
	Alkash(int ttd = 0, int tte = 0, int tts = 0, int ttt = 0);
	~Alkash() {};
	Alkash(const Alkash& obj);
	Alkash&	operator=(const Alkash& obj);

	void	buchat();
	void	sleep(long sleep = -1);
	void	finding(long t_fb = -1);
	long	checktime();
};

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

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::milliseconds;

class	Alkash
{
	int								t_td;
	int								t_te;
	int								t_ts;
	int								t_tt;
	long							timer;
	std::chrono::time_point<Clock>	start;
	std::chrono::time_point<Clock>	end;
public:
	Alkash(int ttd = 0, int tte = 0, int tts = 0, int ttt = 0);
	~Alkash() {};
	Alkash(const Alkash& obj);
	Alkash&	operator=(const Alkash& obj);

	void	eat();
	void	sleep();
	void	think();
};
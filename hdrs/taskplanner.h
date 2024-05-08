/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:21:46 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/08 14:13:19 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "alkash.h"
#include <thread>
#include <condition_variable>

using namespace std;

namespace	alkashi_sim
{

using t_cv = condition_variable;

class	TaskPlanner
{
	t_uchar				status;
	long				minchecktime;
	int					count;
	int					eating_tms;
	int					insp_frequency;
	float				lastcheck;
	Alkash				*alkashi;
	Buchlo				*buchlo;
	thread				*threads;
	thread				planer;
	mutex				out_mt;
	mutex				planer_mt;
	mutex				lastcheck_mt;
	t_cv				cv;
	int					correcti(int num);
	void				clear_mem();
	void				planing(int num);
	void				zapoj(int num);
	t_uchar				checkbuchlo(int num);
	bool				checkalkashi(const int& num);
	void				checkalkashi();
public:
	Timer<float>	timer;
	TaskPlanner(int count = 1, long sleep_tm = 0, long eat_tm = 0, long die_tm = 0);
	TaskPlanner(const TaskPlanner& obj);
	~TaskPlanner();
	TaskPlanner&	operator=(const TaskPlanner& obj);
	void			set_ents(int eating_tms = 0);
	void			startsimulation();
	void			startsimplanner();
};

}

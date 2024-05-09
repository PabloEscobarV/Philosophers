/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:21:46 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/09 14:48:02 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "alkash.h"
#include <thread>
#include <condition_variable>

using namespace std;

namespace	alkashi_sim
{

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
	t_cv				cv_buhclo;
	int					correcti(int num);
	void				clear_mem();
	void				planing(int num);
	void				zapoj(int num);
	void				planner(int num);
	t_uchar				checkbuchlo(int num);
	t_uchar				checkpermition(int num);
	t_uchar				checkabpility(int num);
	bool				checkalkashi(const int& num);
	void				checkalkashi();
	bool				checkalkash_lf(const int& num);
public:
	Timer<float>	timer;
	TaskPlanner(int count = 1, long sleep_tm = 0, long eat_tm = 0, long die_tm = 0);
	TaskPlanner(const TaskPlanner& obj);
	~TaskPlanner();
	TaskPlanner&	operator=(const TaskPlanner& obj);
	void			set_ents(int eating_tms = 0);
	void			startsimulation();
	void			startsimplanner();
	void			startplanner();
};

}

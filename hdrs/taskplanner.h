/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:21:46 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/04 13:58:12 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "alkash.h"
#include <thread>

using namespace std;

namespace	alkashi_sim
{

class	TaskPlanner
{
	int		count;
	int		eating_tms;
	Alkash	*alkashi;
	Buchlo	*buchlo;
	thread	*threads;
	mutex	out_mt;
	mutex	planer_mt;
	int		correcti(int num);
	void	clear_mem();
	void	planing(int num);
	int		checkbuchlo(int num);
	bool	checkalkashi();
public:
	TaskPlanner(int count = 1, long sleep_tm = 0, long eat_tm = 0, long die_tm = 0);
	TaskPlanner(const TaskPlanner& obj);
	~TaskPlanner();
	TaskPlanner&	operator=(const TaskPlanner& obj);
	void			set_ents(int eating_tms = 0);
	void			startsimulation();
};

}

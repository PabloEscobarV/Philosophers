/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buchlo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:14:29 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/09 14:50:50 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

namespace	alkashi_sim
{
using namespace std;
using t_cv = condition_variable;

class	Buchlo
{
	bool		status;
	int			id;
public:
	Buchlo(int id = 0);
	Buchlo(const Buchlo& obj);
	~Buchlo();
	Buchlo&	operator=(const Buchlo& obj);
	void	set_id(int _id);
	int		get_id();
	void	lock();
	void	unlock(t_cv& cv);
	void	unlock();
	bool	state();
	friend ostream&	operator<<(ostream& os, const Buchlo& obj);
};
}

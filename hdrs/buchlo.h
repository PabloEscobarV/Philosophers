/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buchlo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:14:29 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/04 13:29:27 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <mutex>
#include <thread>
#include <iostream>

namespace	alkashi_sim
{
using namespace std;

class	Buchlo
{
	bool		status;
	int			id;
	mutex		mt;
public:
	Buchlo(int id = 0);
	Buchlo(const Buchlo& obj);
	~Buchlo();
	Buchlo&	operator=(const Buchlo& obj);
	void	set_id(int _id);
	int		get_id();
	void	lock();
	void	unlock();
	bool	state();
	friend ostream&	operator<<(ostream& os, const Buchlo& obj);
};
}

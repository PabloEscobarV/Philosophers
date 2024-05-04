/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:17:15 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/04 13:28:52 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include "buchlo.h"
#include <thread>

namespace	alkashi_sim
{
	using namespace std;
	
	class	Alkash
{
	bool			buchat_permit;
	int				id;
	float			time_exec;
	long			sleep_t;
	long			buchat_t;
	long			die_t;
	long			metrics;
	Buchlo*			buchlo;
	Buchlo*			zapyvon;
public:
	Timer<float>	timer;
	Alkash(int id = 0, long buchat = 0, long sleep = 0, long die = 0);
	Alkash(const Alkash& obj);
	~Alkash();
	Alkash&			operator=(const Alkash& obj);
	void			setmetrics(long metrics);
	void			getBuchlo(Buchlo& buchlo, Buchlo& zapyvon);
	bool			buchat(mutex& mt, long t = 0);
	void			sleep(mutex& mt, long t = 0);
	void			finding(mutex& mt);
	long			gebuchat();
	long			getsleep();
	long			getdie();
	int				get_id();
};
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alkash.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:17:15 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/09 14:51:18 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include "buchlo.h"
#include <thread>

namespace	alkashi_sim
{
	#define DIE_STATE		0
	#define	ALIVE_STATE		1
	#define BUCHAT_PERM		1
	#define	UCHAR_MASK		255

	enum
	{
		LIFE_STATE,
		PERMITION_BUCHAT,
		IS_LOCKED,
		IS_BUCHING,
		IS_SLEEPING,
		IS_FINDING
	};

	using t_uchar = unsigned char;
	using namespace std;
	
	class	Alkash
{
	t_uchar			status;
	int				id;
	float			time_exec;
	float			last_btm;
	long			sleep_tm;
	long			buchat_tm;
	long			die_tm;
	float			die_mtm;
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
	bool			buchat(mutex& mt, t_cv& cv, long t = 0);
	bool			buchat(mutex& mt, long t = 0);
	void			sleep(mutex& mt, long t = 0);
	void			finding(mutex& mt);
	long			gebuchat();
	long			getsleep();
	long			getdie();
	int				get_id();
	bool			lifestatus();
	t_uchar			state();
	void			die_msg(mutex& mt, const char *msg);
	void			setpermition(t_uchar perm = 1);
};
	void			setbit(t_uchar& data, t_uchar bit = 0, t_uchar val = 1);
	t_uchar			getbit(t_uchar data, t_uchar bit = 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:30 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/17 09:23:53 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <unistd.h>

void	a_sleep(t_alkash *alkash)
{
	pthread_mutex_lock(&alkash->polyana->mutexes[SETST_MT]);
	resetbit(&alkash->status, IS_BUCHING);
	setbit(&alkash->status, IS_SLEEPING);
	pthread_mutex_unlock(&alkash->polyana->mutexes[SETST_MT]);
	printmsg(alkash, "is sleepling");
    usleep(alkash->polyana->times->sleep_tm * METRICS);
}

void	finding(t_alkash *alkash)
{
	if (getbit(alkash->status, IS_FIDING))
		return ;
	pthread_mutex_lock(&alkash->polyana->mutexes[SETST_MT]);
	resetbit(&alkash->status, IS_SLEEPING);
	setbit(&alkash->status, IS_FIDING);
	pthread_mutex_unlock(&alkash->polyana->mutexes[SETST_MT]);
	printmsg(alkash, "is finding");
}

t_uchar	getbuchlo(t_alkash *alkash)
{
	int	i;

	i = correcti(alkash);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
		return (0);
	pthread_mutex_lock(&alkash->polyana->mutexes[GETBUCHLO_MT]);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
	{
		pthread_mutex_unlock(&alkash->polyana->mutexes[GETBUCHLO_MT]);
		return (0);
	}
	alkash->polyana->buchlo[alkash->id] = BUCHLO_LOCK;
	alkash->polyana->buchlo[i] = BUCHLO_LOCK;
	pthread_mutex_unlock(&alkash->polyana->mutexes[GETBUCHLO_MT]);
	setbitlock(alkash, IS_LOCKED);
	printmsg(alkash, "has taken fork`s!!!");
	return (1);
}

t_uchar	buchat(t_alkash *alkash)
{
    if (!getbit(alkash->status, IS_LOCKED) ||
		!getbit(alkash->status, LIFE_STATUS))
        return (0);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm)
	{
		pthread_mutex_lock(&alkash->polyana->mutexes[SETST_MT]);
		setdead(alkash);
		pthread_mutex_unlock(&alkash->polyana->mutexes[SETST_MT]);
		printmsg(alkash, "is DEAD!!!");
		return (0);
	}
	pthread_mutex_lock(&alkash->polyana->mutexes[SETST_MT]);
	setbit(&alkash->status, IS_BUCHING);
	resetbit(&alkash->status, IS_FIDING);
	pthread_mutex_unlock(&alkash->polyana->mutexes[SETST_MT]);
	printmsg(alkash, "is BUCHAJE");
	usleep(alkash->polyana->times->buchat_tm * METRICS);
	gettimeofday(&alkash->buchal_tm, NULL);
	return (1);
}

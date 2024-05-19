/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:30 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/18 17:20:16 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <unistd.h>

void	a_sleep(t_alkash *alkash)
{
	resetbitlock(&alkash->cmnstate, IS_BUCHING, &alkash->polyana->mts[STTS_MT]);
	setbit(&alkash->status, IS_SLEEPING);
	printmsg(alkash, "is sleepling");
	usleep(alkash->polyana->times->sleep_tm * METRICS);
}

void	finding(t_alkash *alkash)
{
	if (getbit(&alkash->status, IS_FIDING))
		return ;
	resetbit(&alkash->status, IS_SLEEPING);
	setbit(&alkash->status, IS_FIDING);
	printmsg(alkash, "is finding");
}

t_uchar	getbuchlo(t_alkash *alkash)
{
	int	i;

	i = correcti(alkash);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
		return (0);
	pthread_mutex_lock(&alkash->polyana->mts[GETBUCHLO_MT]);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
	{
		pthread_mutex_unlock(&alkash->polyana->mts[GETBUCHLO_MT]);
		return (0);
	}
	alkash->polyana->buchlo[alkash->id] = BUCHLO_LOCK;
	alkash->polyana->buchlo[i] = BUCHLO_LOCK;
	pthread_mutex_unlock(&alkash->polyana->mts[GETBUCHLO_MT]);
	setbit(&alkash->status, IS_LOCKED);
	printmsg(alkash, "has taken fork`s!!!");
	return (1);
}

t_uchar	buchat(t_alkash *alkash)
{
	if (!getbit(&alkash->status, IS_LOCKED) || !getbitlock(&alkash->cmnstate,
			LIFE_STATUS, &alkash->polyana->mts[STTS_MT]))
		return (0);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm)
	{
		setdeadlk(alkash);
		printmsg(alkash, "is DEAD!!!");
		return (0);
	}
	setbitlock(&alkash->cmnstate, IS_BUCHING, &alkash->polyana->mts[STTS_MT]);
	resetbit(&alkash->status, IS_FIDING);
	printmsg(alkash, "is BUCHAJE");
	increascounter(alkash);
	usleep(alkash->polyana->times->buchat_tm * METRICS);
	gettimeofday(&alkash->buchal_tm, NULL);
	return (1);
}

void	putbuchlo(t_alkash *alkash)
{
	int	i;

	i = correcti(alkash);
	alkash->polyana->buchlo[alkash->id] = 0;
	alkash->polyana->buchlo[i] = 0;
	resetbit(&alkash->status, IS_LOCKED);
	pthread_mutex_lock(&alkash->polyana->mts[STTS_MT]);
	resetbit(&alkash->cmnstate, PERMITION);
	setbit(&alkash->polyana->alkashi[i]->cmnstate, PERMITION);
	pthread_mutex_unlock(&alkash->polyana->mts[STTS_MT]);
}

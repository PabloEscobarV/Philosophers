/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:30 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/22 20:38:31 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <unistd.h>

void	a_sleep(t_alkash *alkash)
{
	resetbitlock(&alkash->cmnstate, IS_BUCHING, &alkash->polyana->mts[STTS_MT]);
	setbit(&alkash->status, IS_SLEEPING);
	printmsg(alkash, "is sleepling", CYAN);
	usleep(alkash->polyana->times->sleep_tm);
}

void	finding(t_alkash *alkash)
{
	resetbit(&alkash->status, IS_SLEEPING);
	setbit(&alkash->status, IS_FIDING);
	printmsg(alkash, "is finding", YELLOW);
}

t_uchar	getbuchlo(t_alkash *alkash)
{
	int	i;

	i = correcti(alkash);
	pthread_mutex_lock(&alkash->polyana->mts[BUCHLO_MT]);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
	{
		pthread_mutex_unlock(&alkash->polyana->mts[BUCHLO_MT]);
		return (0);
	}
	alkash->polyana->buchlo[alkash->id] = BUCHLO_LOCK;
	alkash->polyana->buchlo[i] = BUCHLO_LOCK;
	pthread_mutex_unlock(&alkash->polyana->mts[BUCHLO_MT]);
	setbit(&alkash->status, IS_LOCKED);
	printmsg(alkash, "has taken fork`s!!!", MAGENTA);
	return (1);
}

t_uchar	buchat(t_alkash *alkash)
{
	if (!getbit(&alkash->status, IS_LOCKED) || !getbitlock(&alkash->cmnstate,
			LIFE_STATUS, &alkash->polyana->mts[STTS_MT]))
		return (0);
	setbitlock(&alkash->cmnstate, IS_BUCHING, &alkash->polyana->mts[STTS_MT]);
	resetbit(&alkash->status, IS_FIDING);
	printmsg(alkash, "is BUCHAJE", GREEN);
	increascounter(alkash);
	setmbuchal_tm(alkash);
	usleep(alkash->polyana->times->buchat_tm);
	return (1);
}

void	putbuchlo(t_alkash *alkash)
{
	int	i;

	i = correcti(alkash);
	pthread_mutex_lock(&alkash->polyana->mts[BUCHLO_MT]);
	alkash->polyana->buchlo[alkash->id] = 0;
	alkash->polyana->buchlo[i] = 0;
	pthread_mutex_unlock(&alkash->polyana->mts[BUCHLO_MT]);
	resetbit(&alkash->status, IS_LOCKED);
	pthread_mutex_lock(&alkash->polyana->mts[STTS_MT]);
	resetbit(&alkash->cmnstate, PERMITION);
	setbit(&alkash->polyana->alkashi[i]->cmnstate, PERMITION);
	pthread_mutex_unlock(&alkash->polyana->mts[STTS_MT]);
}

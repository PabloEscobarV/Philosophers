/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_II.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:09:07 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/18 17:20:54 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <unistd.h>

int	correcti(t_alkash *alkash)
{
	int	i;

	i = alkash->id + 1;
	if (i >= alkash->polyana->count)
		return (0);
	return (i);
}

void	setdead(t_alkash *alkash)
{
	resetbit(&alkash->cmnstate, LIFE_STATUS);
	alkash->tm_dead = tm_sec_f(&alkash->timer);
	if (!getbit(&alkash->polyana->status, IS_DEAD))
		setbit(&alkash->polyana->status, IS_DEAD);
}

void	setdeadlk(t_alkash *alkash)
{
	resetbitlock(&alkash->cmnstate, LIFE_STATUS,
		&alkash->polyana->mts[STTS_MT]);
	alkash->tm_dead = tm_sec_f(&alkash->timer);
	pthread_mutex_lock(&alkash->polyana->mts[DEAD_MT]);
	if (!getbit(&alkash->polyana->status, IS_DEAD))
		setbit(&alkash->polyana->status, IS_DEAD);
	pthread_mutex_unlock(&alkash->polyana->mts[DEAD_MT]);
}

void	increascounter(t_alkash *alkash)
{
	if (alkash->polyana->times->nofepme < 0)
	{
		++alkash->numbuch;
		return ;
	}
	pthread_mutex_lock(&alkash->polyana->mts[COUNTER_MT]);
	++alkash->numbuch;
	pthread_mutex_unlock(&alkash->polyana->mts[COUNTER_MT]);
}

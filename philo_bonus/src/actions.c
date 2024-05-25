/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:55:50 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/25 13:36:46 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

t_uchar	getbuchlo(t_alkash	*alkash)
{
	int	i;

	if (!getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
		return (0);
	i = alkash->polyana->count_edev;
	sem_wait(alkash->polyana->perm_sm[alkash->id]);
	while (i)
	{
		if (sem_wait(alkash->polyana->buchlo_sm))
		{
			printf("BAD SEM_WAIT OPERATION!!!\n");
			exit(-1);
		}
		--i;
	}
	setbit(&alkash->state, IS_LOCKED);
	printmsg(alkash, "has taken buchat devices");
	return (1);
}

t_uchar	buchat(t_alkash *alkash)
{
	if (!getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
		return (0);
	resetbit(&alkash->state, IS_FIDING);
	setbit(&alkash->state, IS_BUCHING);
	printmsg(alkash, "is BUCHING");
	increaslock(alkash);
	setlastbuchtmlock(alkash);
	usleep(alkash->polyana->times->buchat_tm * METRICS);
	return (0);
}

void	putbuchlo(t_alkash *alkash)
{
	int	i;

	if (!getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
		if (!getbit(&alkash->state, IS_LOCKED))
			return ;
	i = alkash->polyana->count_edev;
	resetbit(&alkash->state, IS_LOCKED);
	sem_post(alkash->polyana->perm_sm[correcti(alkash)]);
	while (i)
	{
		if (sem_post(alkash->polyana->buchlo_sm))
		{
			printf("BAD SEM_WAIT OPERATION!!!\n");
			exit(-1);
		}
		--i;
	}
}

void	a_sleep(t_alkash *alkash)
{
	if (!getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
		return ;
	resetbit(&alkash->state, IS_BUCHING);
	setbit(&alkash->state, IS_SLEEPING);
	printmsg(alkash, "is SLEEPING");
	usleep(alkash->polyana->times->sleep_tm * METRICS);
}

void	finding(t_alkash *alkash)
{
	if (!getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
		return ;
	if (getbit(&alkash->state, IS_FIDING))
		return ;
	resetbit(&alkash->state, IS_SLEEPING);
	setbit(&alkash->state, IS_FIDING);
	printmsg(alkash, "is FINDING");
}

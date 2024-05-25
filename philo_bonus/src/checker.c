/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:28:45 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/25 18:16:51 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

t_uchar	checknumbuchtm(t_alkash *alkash)
{
	if (alkash->polyana->times->nofepme < 0)
		return (0);
	sem_wait(alkash->sems[NUMBUCHTM]);
	if (alkash->numbuch > alkash->polyana->times->nofepme)
	{
		sem_post(alkash->sems[NUMBUCHTM]);
		return (1);
	}
	sem_post(alkash->sems[NUMBUCHTM]);
	return (0);
}

t_uchar	checkdeath(t_alkash *alkash)
{
	sem_wait(alkash->sems[TIMESM]);
	if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
	{
		printmsgcolor(alkash, "is DEAD!!!", RED);
		sem_post(alkash->sems[TIMESM]);
		return (1);
	}
	sem_post(alkash->sems[TIMESM]);
	return (0);
}

void	*checker(void *data)
{
	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
	{
		usleep(CHECKTIME * METRICS);
		if (checkdeath(alkash) || checknumbuchtm(alkash))
		{
			resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]);
			sem_post(alkash->polyana->semaphrs[DEATHSM]);
			return (NULL);
		}
	}
	return (NULL);
}

void	*deathcontrol(void *data)
{
	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	sem_wait(alkash->polyana->semaphrs[DEATHSM]);
	resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]);
	sem_post(alkash->polyana->semaphrs[DEATHSM]);
	return (NULL);
}

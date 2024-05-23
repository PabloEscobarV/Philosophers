/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:20:32 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 15:57:51 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <signal.h>

t_uchar	checkdeath(t_alkash *alkash)
{
	if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
	{
		resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]);
		return (1);
	}
	return (0);
}

void	*checker(void *data)
{
	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
	{
		usleep(CHECKTIME * METRICS);
		if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
		{
			printmsgcolor(alkash, "is DEAD!!!", RED);
			resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]);
		}
		if (alkash->polyana->times->nofepme > 0)
		{
			if ()
		}
	}
	return (NULL);
}

void	planner(t_alkash *alkash)
{
	pthread_t	th_check;

	if (!alkash)
	{
		printmsg(alkash, "BAD MEMMORY ALLOCATION!!!!");
		exit(-1);
	}
	pthread_create(&th_check, NULL, checker, alkash);
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
	{
		getbuchlo(alkash);
		buchat(alkash);
		putbuchlo(alkash);
		a_sleep(alkash);
		finding(alkash);
	}
	pthread_join(th_check, NULL);
	free(alkash);
	exit(0);
}

t_uchar	setforks(t_polyana *polyana)
{
	pid_t	id_term;
	int		i;

	i = 0;
	while (i < polyana->count)
	{
		polyana->pids[i] = fork();
		if (polyana->pids[i] < 0)
			return (1);
		if (!polyana->pids[i])
			planner(crtalkash(i, polyana));
		++i;
	}
	id_term = wait(NULL);
	while (i)
		if (polyana->pids[--i] != id_term)
			kill(polyana->pids[i], SIGTERM);
	return (0);
}

t_uchar taskplanner(t_polyana *polyana)
{
	if (!polyana)
		return (1);
	if (setforks(polyana))
		return (1);
	freepolyana(polyana);
	return (0);
}
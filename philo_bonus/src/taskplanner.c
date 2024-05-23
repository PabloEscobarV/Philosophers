/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:20:32 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 14:50:22 by polenyc          ###   ########.fr       */
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
		resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->polyana->semaphrs[STATESM]);
		return (1);
	}
	return (0);
}

void	*checker(void *data)
{
	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	// printmsg(alkash, "CHECK POINT: CHECK`S THREAD HAS STARTED");
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->polyana->semaphrs[STATESM]))
	{
		usleep(CHECKTIME * METRICS);
		if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
		{
			printmsg(alkash, "is DEAD!!!");
			resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->polyana->semaphrs[STATESM]);
		}
		// printmsg(alkash, "CHECK POINT: ------------CHECK-------------");
	}
	// printmsg(alkash, "THE END\n");
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
	// printmsg(alkash, "CHECK POINT 0: ");
	pthread_create(&th_check, NULL, checker, alkash);
	// printmsg(alkash, "CHECK POINT 1");
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->polyana->semaphrs[STATESM]))
	{
		// printmsg(alkash, "CHECK POINT 2");
		getbuchlo(alkash);
		buchat(alkash);
		putbuchlo(alkash);
		a_sleep(alkash);
		finding(alkash);
	}
	// printmsg(alkash, "CHECK POINT: EXIT");
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
	printf("ALL PROCESSES WAS CREATED!!!!\n");
	id_term = wait(NULL);
	while (i)
		if (polyana->pids[--i] != id_term)
			kill(polyana->pids[i], SIGTERM);
	return (0);
}

t_uchar taskplanner(t_polyana *polyana)
{
	int			semval;

	if (!polyana)
		return (1);
	sem_getvalue(polyana->semaphrs[OUTSM], &semval);
	printf("CURENT VALUE OF OUT SEMAPHORE: %d\n", semval);
	if (setforks(polyana))
		return (1);
	freepolyana(polyana);
	return (0);
}
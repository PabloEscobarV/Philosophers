/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:20:32 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 11:18:36 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

t_uchar	checkdeath(t_alkash *alkash)
{
	if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
	{
		resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sem_state);
		return (1);
	}
	return (0);
}

void	*checker(void *data)
{
	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sem_state))
	{
		usleep(CHECKTIME * METRICS);
		if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
			resetbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sem_state);
	}
}

void	planner(t_alkash *alkash)
{
	pthread_t	th_check;

	if (!alkash)
	{
		printmsg(alkash, "BAD MEMMORY ALLOCATION!!!!\n");
		exit(-1);
	}
	printmsg(alkash, "CHECK");
	pthread_create(&th_check, NULL, checker, alkash);
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sem_state))
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
	int		i;
	pid_t	id;

	i = 0;
	planner(crtalkash(i, polyana));
	// while (i < polyana->count)
	// {
	// 	id = fork();
	// 	if (id < 0)
	// 		return (1);
	// 	if (!id)
	// 		planner(crtalkash(i, polyana));
	// 	++i;
	// }
	// while (i)
	// {
	// 	--i;
	// 	wait(NULL);
	// }
	return (0);
}

t_uchar taskplanner(int count, t_times *times)
{
	int			semval;
    t_polyana	*polyana;

	polyana = crtpolyana(count, 2, times);
	if (!polyana)
		return (1);
	sem_getvalue(polyana->out_sm, &semval);
	printf("CURENT VALUE OF OUT SEMAPHORE: %d\n", semval);
	sem_wait(polyana->out_sm);
	sem_post(polyana->out_sm);
	if (setforks(polyana))
		return (1);
	freepolyana(polyana);
	return (0);
}
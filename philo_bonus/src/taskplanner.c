/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:20:32 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/25 14:32:02 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void	planner(t_alkash *alkash)
{
	pthread_t	th_check;
	pthread_t	th_deathcntrl;

	if (!alkash)
	{
		printmsg(alkash, "BAD MEMMORY ALLOCATION!!!!");
		exit(-1);
	}
	if (alkash->polyana->count < 2)
	{
		printmsgcolor(alkash, "is DEAD!!!\n", RED);
		freealkash(alkash);
		exit(0);
	}
	pthread_create(&th_check, NULL, checker, alkash);
	pthread_create(&th_deathcntrl, NULL, deathcontrol, alkash);
	while (getbitlock(&alkash->lifestate, LIFE_STATUS, alkash->sems[LIFESM]))
	{
		getbuchlo(alkash);
		buchat(alkash);
		putbuchlo(alkash);
		a_sleep(alkash);
		finding(alkash);
	}
	pthread_join(th_check, NULL);
	pthread_join(th_deathcntrl, NULL);
	usleep(100000);
	printmsgdatacolor(alkash, "NUMBER OF BUCHAL TIMES:\t", GREEN, alkash->numbuch);
	freealkash(alkash);
	exit(0);
}

t_uchar	setforks(t_polyana *polyana)
{
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
	while (i)
		waitpid(polyana->pids[--i], NULL, 0);
	return (0);
}

t_uchar taskplanner(t_polyana *polyana)
{
	int	val;

	if (!polyana)
	{
		printf("%sERROR!!! Bad argument%s\n", RED, RESET_COLOR);
		return (1);
	}
	sem_getvalue(polyana->semaphrs[DEATHSM], &val);
	printf("VALUE FOR DEATHSM: %d\n", val);
	if (!polyana)
		return (1);
	if (setforks(polyana))
		return (1);
	freepolyana(polyana);
	return (0);
}

// t_uchar	setforks(t_polyana *polyana)
// {
// 	pid_t	id_term;
// 	int		i;

// 	i = 0;
// 	while (i < polyana->count)
// 	{
// 		polyana->pids[i] = fork();
// 		if (polyana->pids[i] < 0)
// 			return (1);
// 		if (!polyana->pids[i])
// 			planner(crtalkash(i, polyana));
// 		++i;
// 	}
// 	id_term = wait(NULL);
// 	while (i)
// 		if (polyana->pids[--i] != id_term)
// 			kill(polyana->pids[i], SIGTERM);
// 	return (0);
// }
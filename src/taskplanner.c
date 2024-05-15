/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/15 16:11:36 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

void	printstatus(int id, t_uchar status)
{
	char	space;
	int		i;

	i = BIT_MAX;
	space = '\0';
	if (getbit(status, LIFE_STATUS))
		printf("ALKASH[%d] is ALIVE\n");
	else
		printf("ALKASH[%d] is DEAD!!!\n");
	printf("STATUS for ALKASH[%d]: %d\t", id);
	while (i)
	{
		if (getbit(status, --i))
			printf("%c1", space);
		else
			printf("%c0", space);
		space = ' ';
	}
	printf("\n");
}

t_uchar	check_dead(t_alkash *alkash)
{
	t_timer	cur_tm;
	
	if (!getbit(alkash->status, LIFE_STATUS))
		return (1);
	if (gettimeofday(&cur_tm, NULL))
		printf("ERROR GETTIMEOFDAY!!!\n");
	if (tm_msec(&cur_tm) - tm_msec(&alkash->buchal_tm) >
		alkash->polyana->times->die_tm)
	{
		resetbit(&alkash->status, LIFE_STATUS);
		return (1);
	}
	return (0);
}

t_uchar	checkalkashi(t_alkash *alkash)
{
	int	i;

	if (getbit(alkash->polyana->status, IS_DEAD))
		return (0);
	if (tm_msec(alkash) - alkash->polyana->lastcheck < CHECKTIME)
		return (1);
	pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
	if (tm_msec(alkash) - alkash->polyana->lastcheck < CHECKTIME)
		return (1);
	alkash->polyana->lastcheck = tm_msec(alkash);
	pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
	i = -1;
	while (i < alkash->polyana->count)
	{
		if (check_dead(alkash))
		{
			pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
			setbit(alkash->polyana->status, IS_DEAD);
			pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
			return (0);
		}
	}
	return (1);
}

void    *planner(void *data)
{
 	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	if (alkash->status)
		return (NULL);
	while (checkalkashi(alkash))
	{
		if (getbuchlo(alkash))
		{
			buchat(alkash);
			putbuchlo(alkash);
			a_sleep(alkash);
			finding(alkash);
		}
	}
	printstatus(alkash->id, alkash->status);
}

t_uchar	taskplanner(int count, t_times *times)
{
    int			i;
	t_uchar		status;
    t_polyana	*polyana;

	polyana = crtpolyana(count, times);
	if (!polyana)
		return (ERROR);
	i = -1;
	while (i < polyana->count)
        if (pthread_create(polyana->threads[++i], NULL, planner, polyana))
		{
			pthread_mutex_lock(&polyana->mutexes[PLANNER_MT]);
			resetbit(&polyana->alkashi[i]->status, LIFE_STATUS);
			pthread_mutex_unlock(&polyana->mutexes[PLANNER_MT]);
			break ;
		}
	while (i)
		if (pthread_join(polyana->threads[--i], NULL))
		{
			pthread_mutex_lock(&polyana->mutexes[PLANNER_MT]);
			resetbit(&polyana->alkashi[i]->status, LIFE_STATUS);
			pthread_mutex_unlock(&polyana->mutexes[PLANNER_MT]);
			break ;
		}
	status = polyana->status;
	freepolyana(polyana);
	return (status);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 12:17:23 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

t_uchar	check_dead(t_alkash *alkash)
{
	if (!getbitlock(alkash->cmnstate, LIFE_STATUS, &alkash->polyana->mutexes[STTS_MT]))
		return (1);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm &&
		!getbitlock(alkash->cmnstate, IS_BUCHING, &alkash->polyana->mutexes[STTS_MT]))
	{
		resetbitlock(&alkash->cmnstate, LIFE_STATUS, &alkash->polyana->mutexes[STTS_MT]);
		return (1);
	}
	return (0);
}

t_uchar	checkalkashi(t_alkash *alkash)
{
	int	i;

	if (tm_sec(&alkash->timer) > EXECTIME)
		setdead(alkash);
	if (tm_msec(&alkash->timer) - alkash->polyana->lastcheck < CHECKTIME)
		return (1);
	pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
	if (tm_msec(&alkash->timer) - alkash->polyana->lastcheck < CHECKTIME)
	{
		pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
		return (1);
	}
	alkash->polyana->lastcheck = tm_msec(&alkash->timer);
	pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
	i = alkash->polyana->count;
	while (i)
	{
		if (check_dead(alkash->polyana->alkashi[--i]))
			setdeadlk(alkash->polyana->alkashi[i]);
	}
	return (1);
}

void    *planner(void *data)
{
 	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	// if (getbitlock(alkash->polyana->status, IS_DEAD, &alkash->polyana->mutexes[DEAD_MT]))
	// 	return (NULL);
	while (!getbitlock(alkash->polyana->status, IS_DEAD, &alkash->polyana->mutexes[DEAD_MT]))
	{
		if (getbitlock(alkash->cmnstate, PERMITION, &alkash->polyana->mutexes[STTS_MT]))
			getbuchlo(alkash);
		if (buchat(alkash))
		{
			putbuchlo(alkash);
			a_sleep(alkash);
		}
		finding(alkash);
		checkalkashi(alkash);
	}
}

void	settreads(t_polyana *polyana)
{
	int	i;
	
	i = 0;
	while (i < polyana->count)
	{
        if (pthread_create(&polyana->threads[i], NULL, planner, polyana->alkashi[i]))
		{
			setbitlock(&polyana->status, IS_DEAD, &polyana->mutexes[DEAD_MT]);
			break ;
		}
		++i;
	}
	while (i)
		if (pthread_join(polyana->threads[--i], NULL))
		{
			setbitlock(&polyana->status, IS_DEAD, &polyana->mutexes[DEAD_MT]);
			break ;
		}
}

t_uchar	taskplanner(int count, t_times *times)
{
	t_uchar		status;
    t_polyana	*polyana;

	polyana = crtpolyana(count, times);
	if (!polyana)
		return (ERROR);
	settreads(polyana);
	for (int i = 0; i < polyana->count; ++i)
		printstatus(polyana->alkashi[i]);
	status = polyana->status;
	freepolyana(polyana);
	return (status);
}

	// pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	// printf("--------------CHECK ID[%d] IN TIME: %d--------------\n",
	// 	alkash->id, alkash->polyana->lastcheck);
	// pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
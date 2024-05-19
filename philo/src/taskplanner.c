/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/19 15:02:04 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

void	*planner(void *data)
{
	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	if (getbitlock(&alkash->polyana->status, IS_DEAD,
			&alkash->polyana->mts[DEAD_MT]))
		return (NULL);
	if (alkash->polyana->count < 2)
		setdeadlk(alkash);
	while (!getbitlock(&alkash->polyana->status, IS_DEAD,
			&alkash->polyana->mts[DEAD_MT]))
	{
		if (getbitlock(&alkash->cmnstate, PERMITION,
				&alkash->polyana->mts[STTS_MT]))
			getbuchlo(alkash);
		if (buchat(alkash))
		{
			putbuchlo(alkash);
			a_sleep(alkash);
		}
		finding(alkash);
		checkalkashi(alkash);
	}
	return (NULL);
}

void	settreads(t_polyana *polyana)
{
	int	i;

	i = 0;
	while (i < polyana->count)
	{
		if (pthread_create(&polyana->threads[i], NULL, planner,
				polyana->alkashi[i]))
		{
			setbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]);
			break ;
		}
		++i;
	}
	while (i)
	{
		if (pthread_join(polyana->threads[--i], NULL))
		{
			setbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]);
			break ;
		}
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
	printstatus(polyana);
	status = polyana->status;
	freepolyana(polyana);
	return (status);
}

	// pthread_mutex_lock(&alkash->polyana->mts[OUT_MT]);
	// printf("--------------CHECK ID[%d] IN TIME: %d--------------\n",
	// 	alkash->id, alkash->polyana->lastcheck);
	// pthread_mutex_unlock(&alkash->polyana->mts[OUT_MT]);
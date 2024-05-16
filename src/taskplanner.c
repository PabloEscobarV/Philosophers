/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/16 16:39:52 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

void	printstatus(t_alkash *alkash)
{
	char	space;
	int		i;

	i = BIT_MAX;
	space = '\0';
	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	if (getbit(alkash->status, LIFE_STATUS))
		printf("ALKASH[%d] is ALIVE\n", alkash->id);
	else
		printf("ALKASH[%d] is DEAD!!!\n", alkash->id);
	// printf("STATUS for ALKASH[%d]: %d\t", alkash->id);
	// while (i)
	// {
	// 	if (getbit(alkash->status, --i))
	// 		printf("%c1", space);
	// 	else
	// 		printf("%c0", space);
	// 	space = ' ';
	// }
	pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
}

t_uchar	check_dead(t_alkash *alkash)
{
	if (!getbit(alkash->status, LIFE_STATUS))
		return (1);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm &&
		!getbit(alkash->status, IS_BUCHING))
	{
		pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
		resetbit(&alkash->status, LIFE_STATUS);
		pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
		return (1);
	}
	return (0);
}

t_uchar	checkalkashi(t_alkash *alkash)
{
	int	i;

	if (tm_msec(&alkash->timer) - alkash->polyana->lastcheck < CHECKTIME)
		return (1);
	pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
	if (tm_msec(&alkash->timer) - alkash->polyana->lastcheck < CHECKTIME)
		return (1);
	alkash->polyana->lastcheck = tm_msec(&alkash->timer);
	pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
	// pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	// printf("-----------------CHECK[%d]: %f--------------------\n", alkash->id,
	// 	tm_sec_f(&alkash->timer));
	// pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
	i = alkash->polyana->count;;
	while (i)
	{
		if (check_dead(alkash->polyana->alkashi[--i]))
		{
			pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
			resetbit(&alkash->status, LIFE_STATUS);
			if (!getbit(alkash->polyana->status, IS_DEAD))
				setbit(&alkash->polyana->status, IS_DEAD);
			pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
		}
	}
	return (1);
}

void    *planner(void *data)
{
 	t_alkash	*alkash;

	alkash = (t_alkash *)data;
	if (!getbit(alkash->status, LIFE_STATUS))
		return (NULL);
	while (!getbit(alkash->polyana->status, IS_DEAD))
	{
		if (getbit(alkash->status, PERMITION))
			getbuchlo(alkash);
		if (buchat(alkash))
		{
			putbuchlo(alkash);
			a_sleep(alkash);
		}
		finding(alkash);
		checkalkashi(alkash);
	}
	usleep(1000);
	printstatus(alkash);
}

t_uchar	taskplanner(int count, t_times *times)
{
    int			i;
	t_uchar		status;
    t_polyana	*polyana;

	polyana = crtpolyana(count, times);
	if (!polyana)
		return (ERROR);
	i = 0;
	while (i < polyana->count)
	{
        if (pthread_create(&polyana->threads[i], NULL, planner, polyana->alkashi[i]))
		{
			pthread_mutex_lock(&polyana->mutexes[PLANNER_MT]);
			resetbit(&polyana->alkashi[i]->status, LIFE_STATUS);
			pthread_mutex_unlock(&polyana->mutexes[PLANNER_MT]);
			break ;
		}
		++i;
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:30 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/15 16:15:41 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

void	a_sleep(t_alkash *alkash)
{
    pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
    printf("TIME: %f\tALKASH[%d] is sleepling\n", tm_sec_f(&alkash->timer));
    pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
    usleep(alkash->polyana->times->sleep_tm * 1000L);
}

void	finding(t_alkash *alkash)
{
    pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
    printf("TIME: %f\tALKASH[%d] is finding\n", tm_sec_f(&alkash->timer));
    pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
}

int		correcti(t_alkash *alkash, int i)
{
	if (i >= alkash->polyana->count)
		return (0);
	return (i);
}

void	putbuchlo(t_alkash *alkash)
{
	alkash->polyana->buchlo[alkash->id] = 0;
	alkash->polyana->buchlo[correcti(alkash, alkash->id + 1)] = 0;
}

t_uchar	getbuchlo(t_alkash *alkash)
{
	int	i;

	if (!getbit(alkash, PERMITION))
		return (0);
	i = correcti(alkash, alkash->id + 1);
	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
		return (0);
	alkash->polyana->buchlo[alkash->id] = IS_LOCKED;
	alkash->polyana->buchlo[i] = IS_LOCKED;
	printf("TIME: %f\tALKASH[%d] has taken fork`s!!!\n",
		tm_sec_f(&alkash->timer), alkash->id);
	pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
	return (1);
}

t_uchar	buchat(t_alkash *alkash)
{
	t_timer	cur_tm;

    if (!getbit(alkash->status, PERMITION) ||
        !getbit(alkash->status, IS_LOCKED))
        return (0);
    if (gettimeofday(&cur_tm, NULL))
		printf("ERROR GETTIMEOFDAY!!!\n");
	if (tm_msec(&cur_tm) - tm_msec(&alkash->buchal_tm) >
		alkash->polyana->times->die_tm)
	{
		resetbit(&alkash->status, LIFE_STATUS);
		return (0);
	}
	alkash->buchal_tm = cur_tm;
	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	printf("TIME: %f\tALKASH[%d] id BUCHAJE\n", tm_sec_f(&alkash->timer),
		alkash->id);
	pthread_mutex_ulock(&alkash->polyana->mutexes[OUT_MT]);
	usleep(alkash->polyana->times->buchat_tm);
	return (1);
}

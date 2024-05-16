/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:30 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/16 16:55:22 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <unistd.h>

void	print(t_alkash *alkash)
{
	char	space;
	int		j;

	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	for (int i = 0; i < alkash->polyana->count; ++i)
	{
		printf("STATUS for ALKASH[%d]:\t", i);
		j = BIT_MAX;
		space = '\0';
		while (j)
		{
			if (getbit(alkash->polyana->alkashi[i]->status, --j))
				printf("%c1", space);
			else
				printf("%c0", space);
			space = ' ';
		}
		printf("\n");
	}
	pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
}

void	a_sleep(t_alkash *alkash)
{
    pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	resetbit(&alkash->status, IS_BUCHING);
	setbit(&alkash->status, IS_SLEEPING);
    printf("TIME: %f\tALKASH[%d] is sleepling\n", tm_sec_f(&alkash->timer),
		alkash->id);
    pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
	print(alkash);
    usleep(alkash->polyana->times->sleep_tm * 1000L);
}

void	finding(t_alkash *alkash)
{
	if (getbit(alkash->status, IS_FIDING))
		return ;
    pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	resetbit(&alkash->status, IS_SLEEPING);
	setbit(&alkash->status, IS_FIDING);
    printf("TIME: %f\tALKASH[%d] is finding\n", tm_sec_f(&alkash->timer),
		alkash->id);
    pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
}

t_uchar	getbuchlo(t_alkash *alkash)
{
	int	i;

	i = correcti(alkash);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
		return (0);
	pthread_mutex_lock(&alkash->polyana->mutexes[GETBUCHLO_MT]);
	if (alkash->polyana->buchlo[alkash->id] || alkash->polyana->buchlo[i])
	{
		pthread_mutex_unlock(&alkash->polyana->mutexes[GETBUCHLO_MT]);
		return (0);
	}
	alkash->polyana->buchlo[alkash->id] = IS_LOCKED;
	alkash->polyana->buchlo[i] = IS_LOCKED;
	setbit(&alkash->status, IS_LOCKED);
	pthread_mutex_unlock(&alkash->polyana->mutexes[GETBUCHLO_MT]);
	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	printf("TIME: %f\tALKASH[%d] has taken fork`s!!!\n",
		tm_sec_f(&alkash->timer), alkash->id);
	pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
	return (1);
}

t_uchar	buchat(t_alkash *alkash)
{
    if (!getbit(alkash->status, IS_LOCKED))
        return (0);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm)
	{
		pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
		resetbit(&alkash->status, LIFE_STATUS);
		pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
		return (0);
	}
	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	setbit(&alkash->status, IS_BUCHING);
	resetbit(&alkash->status, IS_FIDING);
	printf("TIME: %f\tALKASH[%d] is BUCHAJE\n", tm_sec_f(&alkash->timer),
		alkash->id);
	pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
	usleep(alkash->polyana->times->buchat_tm * 1000L);
	gettimeofday(&alkash->buchal_tm, NULL);
	return (1);
}

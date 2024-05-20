/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:55:50 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 17:47:08 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	getbuchlo(t_alkash	*alkash)
{
	int	i;

	i = alkash->polyana->count_edev;
	sem_wait(alkash->polyana->permition[alkash->id]);
	while (i)
	{
		if (sem_wait(alkash->polyana->buchlo))
		{
			printf("BAD SEM_WAIT OPERATION!!!\n");
			exit(-1);
		}
		--i;
	}
	printmsg(alkash, "has taken buchat devices");
}

t_uchar	buchat(t_alkash *alkash)
{
	if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
	{
		resetbit(&alkash->state, LIFE_STATUS);
		return (1);
	}
	resetbit(&alkash->state, IS_FIDING);
	setbit(&alkash->state, IS_BUCHING);
	printmsg(alkash, "is BUCHING\n");
	gettimeofday(&alkash->lastbuchtm, NULL);
	usleep(alkash->polyana->times->buchat_tm * METRICS);

	return (0);
}

void	putbuchlo(t_alkash *alkash)
{
	int	i;

	i = alkash->polyana->count_edev;
	sem_post(alkash->polyana->permition[correcti(alkash)]);
	while (i)
	{
		if (sem_post(alkash->polyana->buchlo))
		{
			printf("BAD SEM_WAIT OPERATION!!!\n");
			exit(-1);
		}
		--i;
	}
}

void	a_sleep(t_alkash *alkash)
{
	resetbit(&alkash->state, IS_BUCHING);
	setbit(&alkash->state, IS_SLEEPING);
	printmsg(alkash, "is SLEEPING");
	usleep(alkash->polyana->times->sleep_tm * METRICS);
}

void	finding(t_alkash *alkash)
{
	if (getbit(alkash->state, IS_FIDING))
		return ;
	resetbit(&alkash->state, IS_SLEEPING);
	setbit(&alkash->state, IS_FIDING);
	printmsg(alkash, "is FINDING");
}

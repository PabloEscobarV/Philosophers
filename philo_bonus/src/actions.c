/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:55:50 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 14:50:31 by polenyc          ###   ########.fr       */
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
	int	semval;
	int	i;

	// sem_getvalue(alkash->polyana->perm_sm[alkash->id], &semval);
	// printf("CURENT VALUE OF OUT SEMAPHORE: %d\n", semval);
	i = alkash->polyana->count_edev;
	sem_wait(alkash->polyana->perm_sm[alkash->id]);
	while (i)
	{
		if (sem_wait(alkash->polyana->buchlo_sm))
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
	// if (tm_msec(&alkash->lastbuchtm) > alkash->polyana->times->die_tm)
	// 	return (setdead(alkash));

	resetbit(&alkash->state, IS_FIDING);
	setbit(&alkash->state, IS_BUCHING);
	printmsg(alkash, "is BUCHING");
	increaslock(&alkash->numbuch, alkash->polyana->semaphrs[BUCHNUMSM]);
	gettimeofday(&alkash->lastbuchtm, NULL);
	usleep(alkash->polyana->times->buchat_tm * METRICS);
	return (0);
}

void	putbuchlo(t_alkash *alkash)
{
	int	i;

	i = alkash->polyana->count_edev;
	sem_post(alkash->polyana->perm_sm[correcti(alkash)]);
	while (i)
	{
		if (sem_post(alkash->polyana->buchlo_sm))
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
	if (getbit(&alkash->state, IS_FIDING))
		return ;
	resetbit(&alkash->state, IS_SLEEPING);
	setbit(&alkash->state, IS_FIDING);
	printmsg(alkash, "is FINDING");
}

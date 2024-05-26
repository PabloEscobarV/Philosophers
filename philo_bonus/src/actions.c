/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:55:50 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 18:19:59 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

t_uchar	getbuchlo(t_alkash	*alkash)
{
	int	i;

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
	setbit(&alkash->state, IS_LOCKED);
	printmsglock(alkash, GETBUCHLOMSG);
	return (1);
}

t_uchar	buchat(t_alkash *alkash)
{
	resetbit(&alkash->state, IS_FIDING);
	setbit(&alkash->state, IS_BUCHING);
	printmsglock(alkash, BUCHATMSG);
	setlastbuchtmlock(alkash);
	usleep(alkash->polyana->times->buchat_tm);
	increaslock(alkash);
	return (0);
}

void	putbuchlo(t_alkash *alkash)
{
	int	i;

	i = alkash->polyana->count_edev;
	resetbit(&alkash->state, IS_LOCKED);
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
	printmsglock(alkash, SLEEPINGMSG);
	usleep(alkash->polyana->times->sleep_tm);
}

void	finding(t_alkash *alkash)
{
	resetbit(&alkash->state, IS_SLEEPING);
	setbit(&alkash->state, IS_FIDING);
	printmsglock(alkash, FINDINGMSG);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:09:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 09:29:03 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

void	printmsg(t_alkash *alkash, const char *msg)
{
	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	printf("%f\t[%d]\t%s\n", tm_sec_f(&alkash->timer), alkash->id, msg);
	pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
}

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
		printf("ALKASH[%d] is DEAD!!! in TIME: %f\n", alkash->id, alkash->tm_dead);
	pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
}

void	print(t_alkash *alkash)
{
	char	space;
	int		j;

	pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	printf("ALKASH[%d]:\n", alkash->id);
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

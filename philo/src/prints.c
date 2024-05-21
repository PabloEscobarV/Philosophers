/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:09:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/21 14:04:08 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

void	printmsg(t_alkash *alkash, const char *msg)
{
	pthread_mutex_lock(&alkash->polyana->mts[OUT_MT]);
	printf("%f\t[%d]\t%s\n", tm_sec_f(&alkash->timer), alkash->id, msg);
	pthread_mutex_unlock(&alkash->polyana->mts[OUT_MT]);
}

void	print_msg(t_polyana *polyana, const char *msg)
{
	pthread_mutex_lock(&polyana->mts[OUT_MT]);
	printf("%f\t%s\n", tm_sec_f(&polyana->timer), msg);
	pthread_mutex_unlock(&polyana->mts[OUT_MT]);
}

void	printstatus(t_polyana *polyana)
{
	int	i;

	i = 0;
	while (i < polyana->count)
	{
		if (getbit(&polyana->alkashi[i]->cmnstate, LIFE_STATUS))
			printf("ALKASH[%d] is ALIVE\tNumber of BUCHAL times: %d\n",
				polyana->alkashi[i]->id, polyana->alkashi[i]->numbuch);
		else
			printf(
				"ALKASH[%d] is DEAD!!! in TIME: %f\tNum of BUCHAL times: %d\n",
				polyana->alkashi[i]->id, polyana->alkashi[i]->tm_dead,
				polyana->alkashi[i]->numbuch);
		++i;
	}
}

void	printdead(t_alkash *alkash)
{
	if (getbit(&alkash->cmnstate, LIFE_STATUS))
		return ;
	printf("ALKASH[%d] is DEAD!!! in TIME: %f\tNumber of BUCHAL times: %d\n",
		alkash->id, alkash->tm_dead, alkash->numbuch);
}

void	printdeadlk(t_alkash *alkash)
{
	if (getbit(&alkash->cmnstate, LIFE_STATUS))
		return ;
	pthread_mutex_lock(&alkash->polyana->mts[OUT_MT]);
	printf("ALKASH[%d] is DEAD!!! in TIME: %f\tNumber of BUCHAL times: %d\n",
		alkash->id, alkash->tm_dead, alkash->numbuch);
	pthread_mutex_unlock(&alkash->polyana->mts[OUT_MT]);
}

void	printbits(t_alkash *alkash)
{
	char	space;
	int		i;
	int		j;

	pthread_mutex_lock(&alkash->polyana->mts[OUT_MT]);
	printf("ALKASH[%d]:\n", alkash->id);
	i = -1;
	while (i < alkash->polyana->count)
	{
		printf("STATUS for ALKASH[%d]:\t", ++i);
		j = BIT_MAX;
		space = '\0';
		while (j)
		{
			if (getbit(&alkash->polyana->alkashi[i]->status, --j))
				printf("%c1", space);
			else
				printf("%c0", space);
			space = ' ';
		}
		printf("\n");
	}
	pthread_mutex_unlock(&alkash->polyana->mts[OUT_MT]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:09:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/27 11:06:26 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

void	printmsg(t_alkash *alkash, const char *msg, const char *color)
{
	pthread_mutex_lock(&alkash->polyana->mts[OUT_MT]);
	printf("%s%li\t%d\t%s%s\n", color, tm_msec(&alkash->timer),
		alkash->id, msg, RESET_COLOR);
	pthread_mutex_unlock(&alkash->polyana->mts[OUT_MT]);
}

void	printstatus(t_polyana *polyana, const char *msg)
{
	int	i;

	i = 0;
	while (i < polyana->count)
	{
		if (getbit(&polyana->alkashi[i]->cmnstate, LIFE_STATUS))
			printf("%sALKASH[%d] is ALIVE\t%s:\t%d%s\n",
				GREEN, polyana->alkashi[i]->id, msg,
				polyana->alkashi[i]->numbuch, RESET_COLOR);
		else
			printf(
				"%sALKASH[%d] was DEAD!!! in: %f\t%s:\t%d%s\n",
				RED, polyana->alkashi[i]->id, polyana->alkashi[i]->tm_dead,
				msg, polyana->alkashi[i]->numbuch, RESET_COLOR);
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

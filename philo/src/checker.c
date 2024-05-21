/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:58:41 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/21 15:32:07 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <unistd.h>

t_uchar	check_dead(t_alkash *alkash)
{
	if (!getbitlock(&alkash->cmnstate, LIFE_STATUS,
			&alkash->polyana->mts[STTS_MT]))
		return (1);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm)
	{
		resetbitlock(&alkash->cmnstate, LIFE_STATUS,
			&alkash->polyana->mts[STTS_MT]);
        alkash->tm_dead = tm_sec_f(&alkash->timer);
        printmsg(alkash, "is DEAD!!!");
		return (1);
	}
	return (0);
}

void	checkalkashi(t_polyana *polyana)
{
    t_uchar isdead;
	t_uchar	allbuchal;
	int		i;

	allbuchal = 1;
	i = polyana->count;
    isdead = 0;
	while (i)
	{
		if (check_dead(polyana->alkashi[--i]))
		{
            if (!isdead)
                isdead = 1;
			continue ;
		}
		if (polyana->times->nofepme > 0)
		{
			pthread_mutex_lock(&polyana->mts[COUNTER_MT]);
			if (polyana->alkashi[i]->numbuch < polyana->times->nofepme)
				allbuchal = 0;
			pthread_mutex_unlock(&polyana->mts[COUNTER_MT]);
		}
	}
	if ((allbuchal && polyana->times->nofepme >= 0) || isdead)
		setbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]);
}

void	*checkpolyana(void *data)
{
	t_polyana	*polyana;

	polyana = (t_polyana *)data;
	while (!getbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]))
	{
		usleep(CHECKTIME * METRICS);
		if (tm_sec(&polyana->timer) > EXECTIME)
			setbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]);
		// print_msg(polyana, "------------CHECK----------------");
		checkalkashi(polyana);
	}
	return (NULL);
}
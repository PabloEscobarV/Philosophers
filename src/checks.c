/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:39:06 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/18 17:22:31 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

t_uchar	check_dead(t_alkash *alkash)
{
	if (!getbitlock(&alkash->cmnstate, LIFE_STATUS,
			&alkash->polyana->mts[STTS_MT]))
		return (1);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm
		&& !getbitlock(&alkash->cmnstate, IS_BUCHING,
			&alkash->polyana->mts[STTS_MT]))
	{
		resetbitlock(&alkash->cmnstate, LIFE_STATUS,
			&alkash->polyana->mts[STTS_MT]);
		return (1);
	}
	return (0);
}

void	checkdata(t_polyana *polyana)
{
	t_uchar	allbuchal;
	int		i;

	allbuchal = 1;
	i = polyana->count;
	while (i)
	{
		if (check_dead(polyana->alkashi[--i]))
		{
			setdeadlk(polyana->alkashi[i]);
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
	if (allbuchal && polyana->times->nofepme > 0)
		setbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]);
}

t_uchar	checkalkashi(t_alkash *alkash)
{
	if (tm_sec(&alkash->timer) > EXECTIME)
		setdeadlk(alkash);
	pthread_mutex_lock(&alkash->polyana->mts[CHECK_MT]);
	if (tm_msec(&alkash->timer) - alkash->polyana->lastcheck < CHECKTIME)
	{
		pthread_mutex_unlock(&alkash->polyana->mts[CHECK_MT]);
		return (1);
	}
	alkash->polyana->lastcheck = tm_msec(&alkash->timer);
	checkdata(alkash->polyana);
	pthread_mutex_unlock(&alkash->polyana->mts[CHECK_MT]);
	return (1);
}

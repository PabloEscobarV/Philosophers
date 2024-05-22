/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:39:06 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/22 20:46:11 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <unistd.h>

t_uchar	checknumbuchal(t_polyana *polyana)
{
	int		i;

	if (polyana->times->nofepme < 0)
		return (0);
	i = 0;
	pthread_mutex_lock(&polyana->mts[COUNTER_MT]);
	if (polyana->alkashi[0]->numbuch < polyana->times->nofepme)
	{
		pthread_mutex_unlock(&polyana->mts[COUNTER_MT]);
		return (0);
	}
	while (i < polyana->count)
	{
		if (polyana->alkashi[i]->numbuch < polyana->times->nofepme)
			break ;
		++i;
	}
	pthread_mutex_unlock(&polyana->mts[COUNTER_MT]);
	if (i >= polyana->count)
		return (1);
	return (0);
}

t_uchar	checkdata(t_polyana *polyana)
{
	t_uchar	isdead;
	int		i;

	i = polyana->count;
	isdead = 0;
	pthread_mutex_lock(&polyana->mts[TIME_MT]);
	while (i)
	{
		if (tm_msec(&polyana->alkashi[--i]->buchal_tm) > polyana->times->die_tm)
		{
			resetbitlock(&polyana->alkashi[i]->cmnstate, LIFE_STATUS,
				&polyana->mts[STTS_MT]);
			polyana->alkashi[i]->tm_dead
				= tm_sec_f(&polyana->alkashi[i]->timer);
			printmsg(polyana->alkashi[i], "is DEAD!!!!", RED);
			++isdead;
		}
	}
	pthread_mutex_unlock(&polyana->mts[TIME_MT]);
	if (isdead)
		return (1);
	return (0);
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
	pthread_mutex_unlock(&alkash->polyana->mts[CHECK_MT]);
	if (checkdata(alkash->polyana) || checknumbuchal(alkash->polyana))
		setbitlock(&alkash->polyana->status, IS_DEAD,
			&alkash->polyana->mts[DEAD_MT]);
	return (1);
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
		if (checkdata(polyana) || checknumbuchal(polyana))
			setbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]);
	}
	return (NULL);
}

// t_uchar	check_dead(t_alkash *alkash)
// {
// 	if (!getbitlock(&alkash->cmnstate, LIFE_STATUS,
// 			&alkash->polyana->mts[STTS_MT]))
// 		return (1);
// 	if (!getbitlock(&alkash->cmnstate, IS_BUCHING,
// 		&alkash->polyana->mts[STTS_MT])
// 			&& tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm)
// 	{
// 		resetbitlock(&alkash->cmnstate, LIFE_STATUS,
// 			&alkash->polyana->mts[STTS_MT]);
// 		return (1);
// 	}
// 	return (0);
// }

// void	checkdata(t_polyana *polyana)
// {
// 	t_uchar	allbuchal;
// 	int		i;

// 	allbuchal = 1;
// 	i = polyana->count;
// 	while (i)
// 	{
// 		if (check_dead(polyana->alkashi[--i]))
// 		{
// 			setdeadlk(polyana->alkashi[i]);
// 			continue ;
// 		}
// 		if (polyana->times->nofepme > 0)
// 		{
// 			pthread_mutex_lock(&polyana->mts[COUNTER_MT]);
// 			if (polyana->alkashi[i]->numbuch < polyana->times->nofepme)
// 				allbuchal = 0;
// 			pthread_mutex_unlock(&polyana->mts[COUNTER_MT]);
// 		}
// 	}
// 	if (allbuchal && polyana->times->nofepme >= 0)
// 		setbitlock(&polyana->status, IS_DEAD, &polyana->mts[DEAD_MT]);
// }

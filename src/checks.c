/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:39:06 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/17 13:53:44 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

t_uchar	check_dead(t_alkash *alkash)
{
	if (!getbitlock(&alkash->cmnstate, LIFE_STATUS, &alkash->polyana->mutexes[STTS_MT]))
		return (1);
	if (tm_msec(&alkash->buchal_tm) > alkash->polyana->times->die_tm &&
		!getbitlock(&alkash->cmnstate, IS_BUCHING, &alkash->polyana->mutexes[STTS_MT]))
	{
		resetbitlock(&alkash->cmnstate, LIFE_STATUS, &alkash->polyana->mutexes[STTS_MT]);
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
		if (polyana->times->nofepme > 0 &&
			polyana->alkashi[i]->numbuch < polyana->times->nofepme)
			allbuchal = 0;
	}
	if (allbuchal && polyana->times->nofepme > 0)
		setbitlock(&polyana->status, IS_DEAD, &polyana->mutexes[DEAD_MT]);
}

t_uchar	checkalkashi(t_alkash *alkash)
{
	int	i;

	if (tm_sec(&alkash->timer) > EXECTIME)
		setdeadlk(alkash);
	pthread_mutex_lock(&alkash->polyana->mutexes[CHECK_MT]);
	if (tm_msec(&alkash->timer) - alkash->polyana->lastcheck < CHECKTIME)
	{
		pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
		return (1);
	}
	alkash->polyana->lastcheck = tm_msec(&alkash->timer);
	checkdata(alkash->polyana);
	pthread_mutex_unlock(&alkash->polyana->mutexes[CHECK_MT]);
	return (1);
}
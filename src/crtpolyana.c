/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtpolyana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:20:24 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/15 13:21:02 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void		*freepolyana(t_polyana *polyana)
{
	if (!polyana)
		return (NULL);
	while (polyana->count)
		free(polyana->alkashi[--polyana->count]);
	free(polyana->alkashi);
	free(polyana->buchlo);
	free(polyana->times);
	free(polyana->mutexes);
	free(polyana->threads);
	free(polyana);
	polyana = NULL;
	return (NULL);
}

t_times		*crttimes(long buchat_tm, long sleep_tm, long die_tm, int nofepme)
{
	t_times	*times;

	if (buchat_tm < 0 || sleep_tm < 0 || die_tm < 0)
		return (NULL);
	times = malloc(sizeof(t_times));
	if (!times)
		return (NULL);
	times->buchat_tm = buchat_tm;
	times->sleep_tm = sleep_tm;
	times->die_tm = die_tm;
	times->nofepme = nofepme;
	return (times);
}

t_alkash	*crtalkash(int id, t_polyana *polyana)
{
	t_alkash	*alkash;

	alkash = malloc(sizeof(t_alkash));
	if (!alkash)
		return (NULL);
	alkash->status = 0;
	alkash->id = id;
	setbit(&alkash->status, LIFE_STATUS);
	if (!(id % 2))
		setbit(&alkash->status, PERMITION);
	alkash->lastcheck = &polyana->lastcheck;
	alkash->g_status = &polyana->status;
	alkash->count = polyana->count;
	alkash->buchlo = polyana->buchlo;
	alkash->mutexes = polyana->mutexes;
	alkash->times = polyana->times;
	alkash->alkashi = polyana->alkashi;
	gettimeofday(&alkash->timer, NULL);
	return (alkash);
}

t_polyana	*mallocpolyana(int count)
{
	t_polyana	*polyana;
	
	polyana = malloc(sizeof(t_polyana));
	if (!polyana)
		return (NULL);
	polyana->alkashi = malloc(count * sizeof(t_alkash **));
	polyana->buchlo = malloc(count * sizeof(t_uchar));
	polyana->mutexes = malloc(MUTEX_COUNT * sizeof(pthread_mutex_t));
	polyana->threads = malloc(count * sizeof(pthread_t));
	if (!polyana->alkashi || !polyana->buchlo || !polyana->mutexes
		|| !polyana->threads)
		return (freepolyana(polyana));
	return (polyana);
}

t_polyana	*crtpolyana(int count, t_times *times)
{
	t_polyana	*polyana;

	if (count < 1 || !times)
		return (NULL);
	polyana = mallocpolyana(count);
	if (!polyana)
		return (NULL);
	polyana->status = 0;
	polyana->count = count;
	polyana->times = times;
	polyana->lastcheck = 0;
	while (count)
	{
		polyana->alkashi[count] = crtalkash(--count, polyana);
		if (!polyana->alkashi[count])
			return (freepolyana(polyana));
		polyana->buchlo[count] = 0;
	}
	if (polyana->count % 2 && polyana->count > 1)
		resetbit(&polyana->alkashi[polyana->count - 1]->status, PERMITION);
	count = MUTEX_COUNT;
	while (count)
		pthread_mutex_init(&polyana->mutexes[--count], NULL);
	return (polyana);
}

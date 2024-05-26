/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtpolyana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:55:08 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 17:35:07 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>

t_times	*crttimes(long die_tm, long buchat_tm, long sleep_tm, int nofepme)
{
	t_times	*times;

	if (buchat_tm < 0 || sleep_tm < 0 || die_tm < 0)
		return (NULL);
	times = malloc(sizeof(t_times));
	if (!times)
		return (NULL);
	times->buchat_tm = buchat_tm * METRICS;
	times->sleep_tm = sleep_tm * METRICS;
	times->die_tm = die_tm;
	times->nofepme = nofepme;
	return (times);
}

char	**crtname(int count, const char *name)
{
	char	**fullnames;

	fullnames = malloc((count + 1) * sizeof(char *));
	if (!fullnames)
		return (NULL);
	fullnames[count] = NULL;
	while (count)
	{
		--count;
		fullnames[count] = ft_strjoinfree((char *)name, ft_itoa(count), 1);
		if (!fullnames[count])
			return (freename(fullnames));
	}
	return (fullnames);
}

t_alkash	*crtalkash(int id, t_polyana *polyana)
{
	char		*tmp;
	t_alkash	*alkash;

	alkash = malloc(sizeof(t_alkash));
	if (!alkash)
		return (NULL);
	setbit(&alkash->lifestate, LIFE_STATUS);
	alkash->numbuch = 0;
	alkash->state = 0;
	alkash->id = id;
	tmp = ft_strjoinfree(SEMSLCNAME, ft_itoa(id), 1);
	alkash->semnames = crtname(COUNTLOCALSM, tmp);
	free(tmp);
	alkash->sems = crtsemaphores(COUNTLOCALSM, (const char **)alkash->semnames);
	if (!alkash->sems)
	{
		free(alkash);
		return (NULL);
	}
	gettimeofday(&alkash->timer, NULL);
	alkash->lastbuchtm = alkash->timer;
	alkash->polyana = polyana;
	return (alkash);
}

t_uchar	checkpolyanaparam(int count, int cnt_dev, t_times *times)
{
	if (count < 1 || cnt_dev < 1)
	{
		free(times);
		return (1);
	}
	if (!times)
		return (1);
	return (0);
}

t_polyana	*crtpolyana(int count, int cnt_dev, t_times *times)
{
	t_polyana	*polyana;

	if (checkpolyanaparam(count, cnt_dev, times))
		return (NULL);
	polyana = malloc(sizeof(t_polyana));
	if (!polyana)
		return (NULL);
	polyana->count = count;
	polyana->count_edev = cnt_dev;
	polyana->times = times;
	polyana->pids = malloc(count * sizeof(pid_t));
	polyana->permname = crtname(count, PERMNAME);
	polyana->semsname = crtname(COUNTSM, SEMSNAME);
	polyana->buchlo_sm = crtsemaphor(BUCHLONAME, count);
	polyana->perm_sm = crtpermsem(polyana->count,
			(const char **)polyana->permname);
	polyana->semaphrs = crtsemaphores(COUNTSM,
			(const char **)polyana->semsname);
	if (!polyana->buchlo_sm || !polyana->perm_sm || !polyana->semaphrs)
		return (freepolyana(polyana));
	sem_wait(polyana->semaphrs[DEATHSM]);
	return (polyana);
}

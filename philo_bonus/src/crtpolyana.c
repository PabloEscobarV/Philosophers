/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtpolyana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:55:08 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/25 14:29:32 by blackrider       ###   ########.fr       */
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
	times->buchat_tm = buchat_tm;
	times->sleep_tm = sleep_tm;
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

sem_t	*crtsemaphor(const char *name, int val)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0666, val);
	if (sem == SEM_FAILED)
	{
		sem_unlink(name);
		sem = sem_open(name, O_CREAT | O_EXCL, 0666, val);
		if (sem == SEM_FAILED)
			return (NULL);
	}
	return (sem);
}

sem_t	**crtpermsem(int count, const char **names)
{
	int		i;
	sem_t	**sem;	

	if (count < 1 || !names || !(*names))
		return (NULL);
	sem = malloc(count * sizeof(sem_t *));
	if (!sem)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (i % 2)
			sem[i] = crtsemaphor(names[i], 1);
		else
			sem[i] = crtsemaphor(names[i], 0);
		if (!sem[i])
			return (freesem(i, names));
		++i;
	}
	return (sem);
}

sem_t		**crtsemaphores(int count, const char **names)
{
	int		i;
	sem_t	**sem;	

	if (count < 1 || !names || !(*names))
		return (NULL);
	sem = malloc(count * sizeof(sem_t *));
	if (!sem)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sem[i] = crtsemaphor(names[i], 1);
		if (!sem[i])
			return (freesem(i, names));
		++i;
	}
	return (sem);
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

t_polyana   *crtpolyana(int count, int cnt_dev, t_times *times)
{
    t_polyana   *polyana;
    
	if (!times || count < 1)
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
	polyana->perm_sm = crtpermsem(polyana->count, (const char **)polyana->permname);
	polyana->semaphrs = crtsemaphores(COUNTSM, (const char **)polyana->semsname);
	if (!polyana->buchlo_sm || !polyana->perm_sm || !polyana->semaphrs)
		return (freepolyana(polyana));
	sem_wait(polyana->semaphrs[DEATHSM]);
	return (polyana);
}
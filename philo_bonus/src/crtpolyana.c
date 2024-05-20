/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtpolyana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:55:08 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 14:04:32 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

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

sem_t	**crtsemaphores(int count, const char **names)
{
	sem_t	**sem;	

	if (count < 1 || !names || !(*names))
		return (NULL);
	sem = malloc(count * sizeof(sem_t *));
	if (!sem)
		return (NULL);
	while (count)
	{
		sem[count] = sem_open(names[--count], O_CREAT, 0666, 1);
		if (sem[count] == SEM_FAILED)
			return (freesem(count, names));
	}
	return (sem);
}

t_polyana   *crtpolyana(int count, t_times *times)
{
    t_polyana   *polyana;
    
    polyana = malloc(sizeof(t_polyana));
	if (!polyana)
		return (NULL);
	polyana->count = count;
	polyana->times = times;
	polyana->buchloname = crtname(count, "BUCHLO.");
	polyana->permname = crtname(count, "PERMITION.");
	polyana->buchlo = crtsemaphores(count, (const char **)polyana->buchloname);
	polyana->permition = crtsemaphores(count, (const char **)polyana->permname);
	if (!polyana->buchlo || !polyana->permition)
		return (freepolyana(polyana));
	return (polyana);
}
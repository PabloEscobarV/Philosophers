/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:44:20 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/24 10:25:28 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <unistd.h>

void	*freename(char **names)
{
	while (*names)
	{
		free(*names);
		++names;
	}
	free(names);
	return (NULL);
}

void	*freesem(int count, const char **names)
{
	while (count)
		sem_unlink(names[--count]);

	return (NULL);
}

void		*freepolyana(t_polyana *polyana)
{
	while (polyana->count)
	{
		sem_close(polyana->perm_sm[--polyana->count]);
		sem_unlink(polyana->permname[polyana->count]);
		free(polyana->permname[polyana->count]);
	}
	polyana->count = COUNTSM;
	while (polyana->count)
	{
		sem_close(polyana->semaphrs[--polyana->count]);
		sem_unlink(polyana->semsname[polyana->count]);
		free(polyana->semsname[polyana->count]);
	}
	sem_close(polyana->buchlo_sm);
	sem_unlink(BUCHLONAME);
	free(polyana->perm_sm);
	free(polyana->semaphrs);
	free(polyana->permname);
	free(polyana->semsname);
	free(polyana->times);
	free(polyana->pids);
	free(polyana);
	polyana = NULL;
	return (polyana);
}

void	*freealkash(t_alkash *alkash)
{
	int	i;

	i = COUNTLOCALSM;
	while (i)
	{
		sem_close(alkash->sems[--i]);
		sem_unlink(alkash->semnames[i]);
		free(alkash->semnames[i]);
	}
	free(alkash->sems);
	free(alkash->semnames);
	free(alkash);
	return (NULL);
}

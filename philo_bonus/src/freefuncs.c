/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:44:20 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 11:17:40 by blackrider       ###   ########.fr       */
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
	sem_close(polyana->buchlo_sm);
	sem_unlink(BUCHLO_SEM);
	free(polyana->perm_sm);
	free(polyana->permname);
	free(polyana->times);
	free(polyana);
	polyana = NULL;
	return (polyana);
}

void	cleanup(t_alkash *alkash)
{
	
}

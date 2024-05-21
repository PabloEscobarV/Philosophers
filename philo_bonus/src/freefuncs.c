/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:44:20 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/21 10:38:00 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>

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
		sem_close(polyana->permition[--polyana->count]);
		sem_unlink(polyana->permname[polyana->count]);
		free(polyana->permname[polyana->count]);
	}
	sem_close(polyana->buchlo);
	sem_unlink(BUCHLO_SEM);
	free(polyana->permition);
	free(polyana->permname);
	free(polyana->times);
	free(polyana);
	polyana = NULL;
	return (polyana);
}

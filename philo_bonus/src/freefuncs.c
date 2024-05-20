/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:44:20 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 14:06:20 by blackrider       ###   ########.fr       */
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
		sem_close(polyana->buchlo[--polyana->count]);
		sem_close(polyana->permition[polyana->count]);
		sem_unlink(polyana->buchloname[polyana->count]);
		sem_unlink(polyana->permname[polyana->count]);
		free(polyana->buchloname[polyana->count]);
		free(polyana->permname[polyana->count]);
	}
	free(polyana->buchlo);
	free(polyana->buchloname);
	free(polyana->permition);
	free(polyana->permname);
	free(polyana->times);
	free(polyana);
	polyana = NULL;
	return (polyana);
}

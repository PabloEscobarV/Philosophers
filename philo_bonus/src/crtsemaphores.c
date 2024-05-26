/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtsemaphores.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:17:45 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 20:16:42 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <fcntl.h>
#include <stdlib.h>

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

sem_t	**crtsemaphores(int count, const char **names)
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

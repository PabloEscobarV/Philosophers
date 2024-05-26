/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtalkashi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:49:44 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 20:35:22 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>

void	freealkashsems(t_alkash *alkash)
{
	int	i;

	i = COUNTLOCALSM;
	while (i)
		sem_unlink(alkash->semnames[--i]);
}

void	*freealkash(t_alkash *alkash)
{
	int	i;

	i = COUNTLOCALSM;
	while (i)
	{
		sem_unlink(alkash->semnames[--i]);
		free(alkash->semnames[i]);
	}
	free(alkash->sems);
	free(alkash->semnames);
	free(alkash);
	return (NULL);
}

t_uchar	crtalkashsems(t_alkash *alkash)
{
	char		*tmp;

	tmp = ft_strjoinfree(SEMSLCNAME, ft_itoa(alkash->id), 1);
	alkash->semnames = crtname(COUNTLOCALSM, tmp);
	free(tmp);
	alkash->sems = crtsemaphores(COUNTLOCALSM, (const char **)alkash->semnames);
	if (!alkash->sems)
		return (1);
	return (0);
}

t_alkash	*crtalkash(int id, t_polyana *polyana)
{
	t_alkash	*alkash;

	if (!polyana)
		return (NULL);
	alkash = malloc(sizeof(t_alkash));
	if (!alkash)
		return (NULL);
	alkash->polyana = polyana;
	alkash->numbuch = 0;
	alkash->state = 0;
	alkash->id = id;
	if (crtalkashsems(alkash))
		return (freealkash(alkash));
	gettimeofday(&alkash->timer, NULL);
	alkash->lastbuchtm = alkash->timer;
	return (alkash);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:20:32 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 15:56:08 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <unistd.h>
#include <sys/wait.h>

void	planner(t_alkash *alkash)
{
	if (!alkash)
	{
		sem_wait(alkash->polyana->out_sem);
		printf("Bad memmory allocation!!!!\n");
		exit(-1);
	}

	free(alkash);
	exit(0);
}

t_uchar	setforks(t_polyana *polyana)
{
	int		i;
	pid_t	id;

	i = 0;
	while (i < polyana->count)
	{
		id = fork();
		if (id < 0)
			return (1);
		if (!id)
			planner(crtalkash(i, polyana));
		++i;
	}
	while (i)
	{
		--i;
		wait(NULL);
	}
	return (0);
}

t_uchar taskplanner(int count, t_times *times)
{
    t_polyana	*polyana;

	polyana = crtpolyana(count, times);
	if (!polyana)
		return (1);
	if (setforks(polyana))
		return (1);
	freepolyana(polyana);
	return (0);
}
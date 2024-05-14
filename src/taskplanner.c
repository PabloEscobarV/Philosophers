/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 14:53:18 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

void    *planner(void *data)
{
 	t_polyana	*polyana;

	polyana = (t_polyana *)data;
	if (getbit())
}

t_uchar	*taskplanner(int count, t_times *times)
{
    int			i;
    t_polyana	*polyana;

	polyana = crtpolyana(count, times);
	if (!polyana)
		return (MEMMORY_ERROR);
	i = -1;
	while (i < polyana->count)
        if (pthread_create(polyana->threads[++i], NULL, planner, polyana))
			polyana->status = ERROR;
	i = -1;
	while (i < polyana->count)
		if (pthread_join(polyana->threads[++i], NULL))
			polyana->status = ERROR;
	return (NULL);
}


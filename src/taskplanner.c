/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskplanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 18:13:04 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

t_uchar	checkalkashi(t_polyana *polyana, int num)
{
	if (getbit(polyana->alkashi))
}

void    *planner(void *data)
{
 	t_polyana	*polyana;

	polyana = (t_polyana *)data;
	if (polyana->status)
		return (NULL);
	while ()
	{

	}
}

t_uchar	taskplanner(int count, t_times *times)
{
    int			i;
	t_uchar		status;
    t_polyana	*polyana;

	polyana = crtpolyana(count, times);
	if (!polyana)
		return (ERROR);
	i = -1;
	while (i < polyana->count)
        if (pthread_create(polyana->threads[++i], NULL, planner, polyana))
		{
			setbit(&polyana->status, ERROR_THCRT);
			break ;
		}
	while (i)
		if (pthread_join(polyana->threads[--i], NULL))
		{
			setbit(&polyana->status, ERROR_THJOIN);
			break ;
		}
	status = polyana->status;
	freepolyana(polyana);
	return (status);
}


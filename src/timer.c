/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:25:39 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/15 14:06:31 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <sys/time.h>
#include <stdlib.h>

long	tm_usec(const t_timer *timer)
{
	t_timer	endtime;

	gettimeofday(&endtime, NULL);
	return (((endtime.tv_sec - timer->tv_sec) * 1000000L) +
		endtime.tv_usec - timer->tv_usec);
}

long	tm_msec(const t_timer *timer)
{
	t_timer	endtime;

	gettimeofday(&endtime, NULL);
	return (((endtime.tv_sec - timer->tv_sec) * 1000L) +
		(endtime.tv_usec - timer->tv_usec) / 1000L);
}

long	tm_sec(const t_timer *timer)
{
	t_timer	endtime;

	gettimeofday(&endtime, NULL);
	return (((endtime.tv_sec - timer->tv_sec)));
}

float	tm_sec_f(const t_timer *timer)
{
	t_timer	endtime;

	gettimeofday(&endtime, NULL);
	return (endtime.tv_sec - timer->tv_sec +
		(endtime.tv_usec - timer->tv_usec) / 1000000.0F);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:25:39 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/15 11:36:06 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <sys/time.h>
#include <stdlib.h>

long	tm_usec(t_alkash *alkash)
{
	t_timer	endtime;

	gettimeofday(&endtime, NULL);
	return (((endtime.tv_sec - alkash->timer.tv_sec) * 1000000L) +
		endtime.tv_usec - alkash->timer.tv_usec);
}

long	tm_msec(t_alkash *alkash)
{
	t_timer	endtime;

	gettimeofday(&endtime, NULL);
	return (((endtime.tv_sec - alkash->timer.tv_sec) * 1000L) +
		(endtime.tv_usec - alkash->timer.tv_usec) / 1000L);
}

long	tm_sec(t_alkash *alkash)
{
	t_timer	endtime;

	gettimeofday(&endtime, NULL);
	return (((endtime.tv_sec - alkash->timer.tv_sec)));
}

float	tm_sec_f(t_alkash *alkash)
{
	return (tm_usec(alkash) / 1000000.0F);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crttimes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:07:49 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/27 11:26:13 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>

int	cornum(const char *data)
{
	if (!data)
		return (-1);
	return ((int)ft_atoi(data));
}

t_times	*crttimes(long die_tm, long buchat_tm, long sleep_tm, int nofepme)
{
	t_times	*times;

	if (buchat_tm < 0 || sleep_tm < 0 || die_tm < 0)
		return (NULL);
	times = malloc(sizeof(t_times));
	if (!times)
		return (NULL);
	times->buchat_tm = buchat_tm * METRICS;
	times->sleep_tm = sleep_tm * METRICS;
	times->die_tm = die_tm;
	times->nofepme = nofepme;
	return (times);
}

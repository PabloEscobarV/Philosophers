/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtpolyana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:20:24 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 14:12:28 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <pthread.h>

void		*freepolyana(t_polyana *polyana)
{
	if (!polyana)
		return (NULL);
	free(polyana->alkashi);
	free(polyana->buchlo);
	free(polyana->threads);
	free(polyana->times);
	free(polyana);
	polyana = NULL;
	return (NULL);
}

t_alkash	*crtalkash()
{
	t_alkash	*alkash;

	alkash = malloc(sizeof(t_alkash));
	if (!alkash)
		return (NULL);
	alkash->status = 0;
	gettimeofday(&alkash->timer, NULL);
	return (alkash);
}

t_times		*crttimes(long buchat_tm, long sleep_tm, long die_tm, int nofepme)
{
	t_times	*times;

	if (buchat_tm < 0 || sleep_tm < 0 || die_tm < 0)
		return (NULL);
	times = malloc(sizeof(t_times));
	if (!times)
		return (NULL);
	times->buchat_tm = buchat_tm;
	times->sleep_tm = sleep_tm;
	times->die_tm = die_tm;
	times->nofepme = nofepme;
	return (times);
}

t_polyana	*crtpolyana(int count, t_times *times)
{
	t_polyana	*polyana;

	if (count < 1 || !times)
		return (NULL);
	polyana = malloc(sizeof(polyana));
	if (!polyana)
		return (NULL);
	polyana->alkashi = malloc(count * sizeof(t_alkash));
	polyana->buchlo = malloc(count * sizeof(t_uchar));
	polyana->threads = malloc(count * sizeof(pthread_t));
	if (!polyana->alkashi || !polyana->buchlo || polyana->threads)
		return (freepolyana(polyana));
	polyana->count = count;
	polyana->times = times;
	polyana->status = 0;
	while (count)
	{
		polyana->alkashi[--count].status = 0;
		gettimeofday(&polyana->alkashi[count].timer, NULL);
		polyana->buchlo[count] = 0;
	}
	return (polyana);
}

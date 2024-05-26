/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtpolyana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:20:24 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 21:19:17 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void	*freepolyana(t_polyana *polyana)
{
	if (!polyana)
		return (NULL);
	while (polyana->count)
		free(polyana->alkashi[--polyana->count]);
	free(polyana->alkashi);
	free(polyana->buchlo);
	free(polyana->times);
	free(polyana->mts);
	free(polyana->threads);
	free(polyana);
	polyana = NULL;
	return (NULL);
}

t_polyana	*mallocpolyana(int count)
{
	t_polyana	*polyana;

	polyana = malloc(sizeof(t_polyana));
	if (!polyana)
		return (NULL);
	polyana->alkashi = malloc(count * sizeof(t_alkash **));
	polyana->buchlo = malloc(count * sizeof(t_uchar));
	polyana->mts = malloc(MUTEX_COUNT * sizeof(pthread_mutex_t));
	polyana->threads = malloc(count * sizeof(pthread_t));
	if (!polyana->alkashi || !polyana->buchlo || !polyana->mts
		|| !polyana->threads)
		return (freepolyana(polyana));
	return (polyana);
}

t_uchar	checkpolyanadata(int count, t_times *times)
{
	if (count < 1)
	{
		printf("%sCOUNT MUST BE MORE THEN ZERO!!!!%s\n", RED, RESET_COLOR);
		free(times);
		return (1);
	}
	if (!times)
		return (1);
	return (0);
}

t_uchar	crtalkashi(int count, t_polyana *polyana)
{
	while (count)
	{
		--count;
		polyana->alkashi[count] = crtalkash(count, polyana);
		if (!polyana->alkashi[count])
			return (1);
		polyana->buchlo[count] = 0;
	}
	return (0);
}

t_polyana	*crtpolyana(int count, t_times *times)
{
	t_polyana	*polyana;

	if (checkpolyanadata(count, times))
		return (NULL);
	polyana = mallocpolyana(count);
	if (!polyana)
		return (NULL);
	polyana->status = 0;
	polyana->count = count;
	polyana->times = times;
	polyana->lastcheck = 0;
	if (crtalkashi(count, polyana))
		return (freepolyana(polyana));
	count = MUTEX_COUNT;
	while (count)
		pthread_mutex_init(&polyana->mts[--count], NULL);
	gettimeofday(&polyana->timer, NULL);
	return (polyana);
}

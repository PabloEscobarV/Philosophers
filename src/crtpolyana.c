/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtpolyana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:20:24 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 13:23:51 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>

void		*freepolyana(t_polyna *polyana)
{
	if (!polyana)
		return (NULL);
	free(polyana->alkashi);
	free(polyana->buchlo);
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

t_polyna	*crtpolyana(int count, long buchat_tm, long sleep_tm, long die_tm)
{
	t_polyna	*polyana;

	polyana = malloc(sizeof(polyana));
	if (!polyana)
		return (NULL);
	polyana->alkashi = malloc((count) * sizeof(t_alkash));
	polyana->buchlo = malloc((count) * sizeof(t_uchar));
	if (!polyana->alkashi || !polyana->buchlo)
		return (freepolyana(polyana));
	polyana->count = count;
	polyana->buchat_tm = buchat_tm;
	polyana->sleep_tm = sleep_tm;
	polyana->die_tm = die_tm;
	while (count)
	{
		polyana->alkashi[--count].status = 0;
		gettimeofday(&polyana->alkashi[count].timer, NULL);
		polyana->buchlo[count] = 0;
	}
	return (polyana);
}

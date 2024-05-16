/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_II.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:09:07 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/16 19:10:44 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <unistd.h>

int		correcti(t_alkash *alkash)
{
	int	i;

	i = alkash->id + 1;
	// pthread_mutex_lock(&alkash->polyana->mutexes[OUT_MT]);
	// printf("CORRECT INDEX: %d\n", i);
	// pthread_mutex_unlock(&alkash->polyana->mutexes[OUT_MT]);
	if (i >= alkash->polyana->count)
		return (0);
	return (i);
}

void	putbuchlo(t_alkash *alkash)
{
	int	i;

	i = correcti(alkash);
	pthread_mutex_lock(&alkash->polyana->mutexes[PUTBUCHLO_MT]);
	alkash->polyana->buchlo[alkash->id] = 0;
	alkash->polyana->buchlo[i] = 0;
	resetbit(&alkash->status, PERMITION);
	resetbit(&alkash->status, IS_LOCKED);
	setbit(&alkash->polyana->alkashi[i]->status, PERMITION);
	pthread_mutex_unlock(&alkash->polyana->mutexes[PUTBUCHLO_MT]);
}

void	setdead(t_alkash *alkash)
{
	resetbit(&alkash->status, LIFE_STATUS);
	alkash->tm_dead = tm_sec_f(&alkash->timer);
	if (!getbit(alkash->polyana->status, IS_DEAD))
		setbit(&alkash->polyana->status, IS_DEAD);
}

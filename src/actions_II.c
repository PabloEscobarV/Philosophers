/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_II.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:09:07 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 11:58:59 by polenyc          ###   ########.fr       */
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

void	setdead(t_alkash *alkash)
{
	resetbit(&alkash->cmnstate, LIFE_STATUS);
	alkash->tm_dead = tm_sec_f(&alkash->timer);
	if (!getbit(alkash->polyana->status, IS_DEAD))
		setbit(&alkash->polyana->status, IS_DEAD);
}

void	setdeadlk(t_alkash *alkash)
{
	resetbitlock(&alkash->cmnstate, LIFE_STATUS, &alkash->polyana->mutexes[STTS_MT]);
	alkash->tm_dead = tm_sec_f(&alkash->timer);
	pthread_mutex_lock(&alkash->polyana->mutexes[DEAD_MT]);
	if (!getbit(alkash->polyana->status, IS_DEAD))
		setbit(&alkash->polyana->status, IS_DEAD);
	pthread_mutex_unlock(&alkash->polyana->mutexes[DEAD_MT]);
}

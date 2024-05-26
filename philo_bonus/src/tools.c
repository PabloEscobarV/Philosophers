/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:31 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 19:50:13 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int	correcti(t_alkash *alkash)
{
	int	i;

	i = alkash->id + 1;
	if (i >= alkash->polyana->count)
		return (0);
	return (i);
}

t_uchar	increaslock(t_alkash *alkash)
{
	if (sem_wait(alkash->sems[NUMBUCHTMSM]))
		return (SEMERROR);
	++alkash->numbuch;
	if (sem_post(alkash->sems[NUMBUCHTMSM]))
		return (SEMERROR);
	return (DEAD);
}

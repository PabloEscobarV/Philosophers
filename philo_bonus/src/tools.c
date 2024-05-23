/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:31 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 13:14:46 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

int	correcti(t_alkash *alkash)
{
	int	i;

	i = alkash->id + 1;
	if (i >= alkash->polyana->count)
		return (0);
	return (i);
}

t_uchar	setdead(t_alkash *alkash)
{
	if (sem_wait(alkash->polyana->semaphrs[STATESM]))
		return (SEMERROR);
	resetbit(&alkash->lifestate, LIFE_STATUS);
	if (sem_post(alkash->polyana->semaphrs[STATESM]))
		return (SEMERROR);
	return (DEAD);
}

void	increaslock(int *data, sem_t *sem)
{
	sem_wait(sem);
	++(*data);
	sem_post(sem);
}
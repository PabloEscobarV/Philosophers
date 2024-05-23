/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitlockoper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:20 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/23 12:31:21 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <semaphore.h>

t_uchar	setbitlock(t_uchar *data, t_uchar bit, sem_t *sem)
{
	t_uchar	tmp;

	if (sem_wait(sem))
		return (SEMERROR);
	if (bit > BIT_MAX)
	{
		if (sem_post(sem))
			return (SEMERROR);
		return (setbitlock(data, ERROR, sem));
	}
	*data |= (t_uchar)1 << bit;
	tmp = *data;
	if (sem_post(sem))
		return (SEMERROR);
	return (tmp);
}

t_uchar	resetbitlock(t_uchar *data, t_uchar bit, sem_t *sem)
{
	t_uchar	tmp;

	if (sem_wait(sem))
		return (SEMERROR);
	if (bit > BIT_MAX)
	{
		if (sem_post(sem))
			return (SEMERROR);
		return (setbitlock(data, ERROR, sem));
	}
	*data &= ~((t_uchar)1 << bit);
	tmp = *data;
	if (sem_post(sem))
		return (SEMERROR);
	return (tmp);
}

t_uchar	getbitlock(t_uchar *data, t_uchar bit, sem_t *sem)
{
	t_uchar	tmp;

	if (sem_wait(sem))
		return (SEMERROR);
	if (bit > BIT_MAX)
	{
		if (sem_post(sem))
			return (SEMERROR);
		return (setbitlock(data, ERROR, sem));
	}
	tmp = *data & ((t_uchar)1 << bit);
	if (sem_post(sem))
		return (SEMERROR);
	return (tmp);
}

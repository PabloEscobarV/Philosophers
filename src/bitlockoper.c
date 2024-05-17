/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitlockoper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:20 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/17 12:08:52 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <pthread.h>

t_uchar	setbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
	{
		pthread_mutex_unlock(mutex);
		return (setbit(data, ERROR));
	}
	*data |= (t_uchar)1 << bit;
	pthread_mutex_unlock(mutex);
	return (*data);
}

t_uchar	resetbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
	{
		pthread_mutex_unlock(mutex);
		return (setbit(data, ERROR));
	}
	*data &= ~((t_uchar)1 << bit);
	pthread_mutex_unlock(mutex);
	return (*data);
}

t_uchar	getbitlock(t_uchar data, t_uchar bit, pthread_mutex_t *mutex)
{
	t_uchar	tmp;

	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
	{
		pthread_mutex_unlock(mutex);
		return (setbit(&data, ERROR));
	}
	tmp = data & ((t_uchar)1 << bit);
	pthread_mutex_unlock(mutex);
	return (tmp);
}

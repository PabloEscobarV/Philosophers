/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitlockoper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:20 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/17 11:05:50 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <pthread.h>

t_uchar	setbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
		return (setbit(data, ERROR));
	*data |= (t_uchar)1 << bit;
	return (*data);
	pthread_mutex_unlock(mutex);
}

t_uchar	resetbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
		return (setbit(data, ERROR));
	*data &= ~((t_uchar)1 << bit);
	return (*data);
	pthread_mutex_unlock(mutex);
}

t_uchar	getbit(t_uchar data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
		return (setbit(&data, ERROR));
	return (data & ((t_uchar)1 << bit));
	pthread_mutex_unlock(mutex);
}

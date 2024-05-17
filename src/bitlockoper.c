/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitlockoper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:20 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/17 13:12:16 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <pthread.h>

void	setbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
	{
		setbit(data, ERROR);
		pthread_mutex_unlock(mutex);
		return ;
	}
	*data |= (t_uchar)1 << bit;
	pthread_mutex_unlock(mutex);
}

void	resetbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
	{
		setbit(data, ERROR);
		pthread_mutex_unlock(mutex);
		return ;
	}
	*data &= ~((t_uchar)1 << bit);
	pthread_mutex_unlock(mutex);
}

t_uchar	getbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	t_uchar	tmp;

	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
	{
		pthread_mutex_unlock(mutex);
		return (setbit(data, ERROR));
	}
	tmp = *data & ((t_uchar)1 << bit);
	pthread_mutex_unlock(mutex);
	return (tmp);
}

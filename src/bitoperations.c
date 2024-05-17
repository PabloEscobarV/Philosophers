/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitoperations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:35:55 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 11:01:44 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
include <pthread.h>

t_uchar	setbit(t_uchar *data, t_uchar bit)
{
	if (bit > BIT_MAX || bit < 0)
		return (setbit(data, ERROR));
	*data |= (t_uchar)1 << bit;
	return (*data);
}

t_uchar	resetbit(t_uchar *data, t_uchar bit)
{
	if (bit > BIT_MAX || bit < 0)
		return (setbit(data, ERROR));
	*data &= ~((t_uchar)1 << bit);
	return (*data);
}

t_uchar	getbit(t_uchar data, t_uchar bit)
{
	if (bit > BIT_MAX || bit < 0)
		return (setbit(&data, ERROR));
	return (data & ((t_uchar)1 << bit));
}

t_uchar	setbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (bit > BIT_MAX || bit < 0)
		return (setbit(data, ERROR));
	*data |= (t_uchar)1 << bit;
	return (*data);
	pthread_mutex_unlock(mutex);
}

t_uchar	resetbitlock(t_alkash *alkash, t_uchar bit)
{
	t_uchar	tmp;

	pthread_mutex_lock(&alkash->polyana->mutexes[SETST_MT]);
	tmp = resetbit(&alkash->status, bit);
	pthread_mutex_unlock(&alkash->polyana->mutexes[SETST_MT]);
	return (tmp);
}

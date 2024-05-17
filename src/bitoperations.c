/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitoperations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:35:55 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 11:34:29 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <pthread.h>

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

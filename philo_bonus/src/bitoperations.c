/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitoperations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:35:55 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 20:27:42 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

t_uchar	setbit(t_uchar *data, t_uchar bit)
{
	if (bit > BIT_MAX)
		return (setbit(data, ERROR));
	*data |= (t_uchar)1 << bit;
	return (*data);
}

t_uchar	resetbit(t_uchar *data, t_uchar bit)
{
	if (bit > BIT_MAX)
		return (setbit(data, ERROR));
	*data &= ~((t_uchar)1 << bit);
	return (*data);
}

t_uchar	getbit(t_uchar *data, t_uchar bit)
{
	if (bit > BIT_MAX)
		return (setbit(data, ERROR));
	return (*data & ((t_uchar)1 << bit));
}

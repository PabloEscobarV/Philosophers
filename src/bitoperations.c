/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitoperations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:35:55 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/13 11:13:43 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

t_uchar	setbit(t_uchar *data, t_uchar bit)
{
	t_uchar	tmp;

	if (bit > BIT_MAX || bit < 0)
		return (MAXBITNUMBER);
	tmp = 1;
	*data |= tmp << bit;
	return (*data);
}

t_uchar	resetbit(t_uchar *data, t_uchar bit)
{
	t_uchar	tmp;

	if (bit > BIT_MAX || bit < 0)
		return (MAXBITNUMBER);
	tmp = 1;
	*data &= ~(tmp << bit);
	return (*data);
}

t_uchar	getbit(t_uchar *data, t_uchar bit)
{
	t_uchar	tmp;

	if (bit > BIT_MAX || bit < 0)
		return (MAXBITNUMBER);
	tmp = 1;
	return (*data & (tmp << bit));
}
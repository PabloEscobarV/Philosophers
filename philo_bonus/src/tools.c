/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:31 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 17:22:51 by blackrider       ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:49:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/24 17:07:34 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

int	main()
{
	int			count = 12;
	t_times		*times;
	t_polyana	*polyana;

	times = crttimes(160, 50, 50, 51);
	polyana = crtpolyana(count, 2, times);
	taskplanner(polyana);
	return (0);
}
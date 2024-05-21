/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:49:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/21 10:39:48 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

int	main()
{
	int			count = 10;
	t_times		*times;
	t_polyana	*polyana;

	times = crttimes(120, 50, 50, -1);
	taskplanner(2, times);
	return (0);
}
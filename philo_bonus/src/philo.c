/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:49:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 14:03:53 by blackrider       ###   ########.fr       */
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
	polyana = crtpolyana(count, times);
	for (int i = 0; i < count; ++i)
	{
		printf("BUCHLO NAME: %s\tPERMITION NAME: %s\n",
			polyana->buchloname[i], polyana->permname[i]);
	}
	freepolyana(polyana);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:49:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/25 13:41:50 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_timer	timer;
	t_times	*times;

	if (argc < 5 || argc > 6)
		return (-1);
	gettimeofday(&timer, NULL);
	times = crttimes(ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), -1);
	if (argv[5])
		times->nofepme = ft_atoi(argv[5]);
	taskplanner(crtpolyana(ft_atoi(argv[1]), 2, times));
	printf("EXECUTION TIME:\t%f\n", tm_sec_f(&timer));
	return (0);
}

// int	main()
// {
// 	int			count = 12;
// 	t_times		*times;
// 	t_polyana	*polyana;

// 	times = crttimes(1600, 500, 500, 10);
// 	polyana = crtpolyana(count, 2, times);
// 	taskplanner(polyana);
// 	return (0);
// }
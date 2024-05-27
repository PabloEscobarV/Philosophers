/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:04:16 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/27 11:26:00 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_timer	timer;
	t_times	*times;

	if (argc < 5 || argc > 6)
		return (-1);
	gettimeofday(&timer, NULL);
	times = crttimes(ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]),
			cornum(argv[5]));
	if (!times)
	{
		printf("%sBAD TIMES ARGUMENTS!!!%s\n", RED, RESET_COLOR);
		return (0);
	}
	taskplanner(ft_atoi(argv[1]), times);
	printf("EXECUTION TIME:\t%f\n", tm_sec_f(&timer));
	return (0);
}

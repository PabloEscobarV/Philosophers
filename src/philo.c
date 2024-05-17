/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:04:16 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 15:01:26 by blackrider       ###   ########.fr       */
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
	times = crttimes(ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), -1);
	if (argv[5])
		times->nofepme = ft_atoi(argv[5]);
	taskplanner(ft_atoi(argv[1]), times);
	printf("EXECUTION TIME:\t%f\n", tm_sec_f(&timer));
	return (0);
}

// void	print_polyana(t_polyana *polyana)
// {
// 	for (int i = 0; i < polyana->count; ++i)
// 	{
// 		printf("ID: %d;\tcount: %d;\tbuchat: %li;\tsleep: %li;\tdie: %li;\tnofepme: %d;\tSTATUS: %d\n",
// 			polyana->alkashi[i]->id, polyana->count, polyana->times->buchat_tm,
// 			polyana->times->sleep_tm, polyana->times->die_tm,
// 			polyana->times->nofepme, polyana->alkashi[i]->status);
// 	}
// 	sleep(2);
// 	printf("TIME[precise sec]: %f\n", tm_sec_f(&polyana->alkashi[0]->timer));
// 	printf("TIME[sec]: %li\n", tm_sec(&polyana->alkashi[0]->timer));
// 	printf("TIME[msec]: %li\n", tm_msec(&polyana->alkashi[0]->timer));
// 	printf("TIME[usec]: %li\n", tm_usec(&polyana->alkashi[0]->timer));
// }

// int	main()
// {
// 	int			count = 11;
// 	t_polyana	*polyana;
// 	t_times		*times;
// 	t_timer		timer;

// 	gettimeofday(&timer, NULL);
// 	times = crttimes(150, 50, 50, 50);
// 	taskplanner(count, times);
// 	printf("EXECUTION TIME:\t%f\n", tm_sec_f(&timer));
// 	return (0);
// }


// int		main()
// {
// 	t_uchar	data;
// 	t_uchar	bit;

// 	bit = 32;
// 	data = 0;
// 	printf("data: %d\n", data);
// 	for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
// 	{
// 		if (getbit(&data, j))
// 			printf("%d ", 1);
// 		else
// 			printf("%d ", 0);
// 	}
// 	printf("\n");
// 	printf("data: %d\n", data);

// 	for (int i = 0; i < sizeof(data) * 8; ++i)
// 	{
// 		setbit(&data, i);
// 		for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
// 		{
// 			if (getbit(&data, j))
// 				printf("%d ", 1);
// 			else
// 				printf("%d ", 0);
// 		}
// 		printf("\n");
// 	}
// 	printf("-----------------------------------------\n");
// 	for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
// 	{
// 		if (getbit(&data, j))
// 			printf("%d ", 1);
// 		else
// 			printf("%d ", 0);
// 	}
// 	printf("\n");
// 	printf("-----------------------------------------\n");
// 	for (int i = 0; i < sizeof(data) * 8; ++i)
// 	{
// 		resetbit(&data, i);
// 		for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
// 		{
// 			if (getbit(&data, j))
// 				printf("%d ", 1);
// 			else
// 				printf("%d ", 0);
// 		}
// 		printf("\n");
// 	}
// 	return (0);
// }

// int main() {
//     int a;
//     int *ptr;
    
//     printf("Size of data type: %zu bytes\n", sizeof(t_alkash));
//     printf("Size of pointer: %zu bytes\n", sizeof(t_alkash*));
    
//     return 0;
// }
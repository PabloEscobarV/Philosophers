/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:04:16 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 11:53:38 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// int	getbit(int *data, int bit)
// {
// 	if (bit > BIT_MAX || bit < 0)
// 		return (setbit(data, ERROR));
// 	return (*data & ((int)1 << bit));
// }

void	print_polyana(t_polyana *polyana)
{
	for (int i = 0; i < polyana->count; ++i)
	{
		printf("ID: %d;\tcount: %d;\tbuchat: %li;\tsleep: %li;\tdie: %li;\tnofepme: %d;\tSTATUS: %d\n",
			polyana->alkashi[i]->id, polyana->count, polyana->times->buchat_tm,
			polyana->times->sleep_tm, polyana->times->die_tm,
			polyana->times->nofepme, polyana->alkashi[i]->status);
	}
	sleep(2);
	printf("TIME[precise sec]: %f\n", tm_sec_f(&polyana->alkashi[0]->timer));
	printf("TIME[sec]: %li\n", tm_sec(&polyana->alkashi[0]->timer));
	printf("TIME[msec]: %li\n", tm_msec(&polyana->alkashi[0]->timer));
	printf("TIME[usec]: %li\n", tm_usec(&polyana->alkashi[0]->timer));
}

int	main()
{
	int			count = 33;
	t_polyana	*polyana;
	t_times		*times;
	t_timer		timer;

	gettimeofday(&timer, NULL);
	times = crttimes(40, 40, 100, -1);
	taskplanner(count, times);
	printf("EXECUTION TIME:\t%f\n", tm_sec_f(&timer));
	return (0);
}


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
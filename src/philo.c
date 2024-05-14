/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:04:16 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 22:01:25 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

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
		printf("ID: %d;\tcount: %d;\tbuchat: %li;\tsleep: %li;\tdie: %li;\tnofepme: %d\n",
			polyana->alkashi[i]->id, polyana->alkashi[i]->count,
			polyana->alkashi[i]->times->buchat_tm, polyana->alkashi[i]->times->sleep_tm,
			polyana->alkashi[i]->times->die_tm, polyana->alkashi[i]->times->nofepme);
	}
}

int	main()
{
	int			count = 10;
	t_polyana	*polyana;
	t_times		*times;

	times = crttimes(10, 10, 11, -1);
	polyana = crtpolyana(count, times);
	print_polyana(polyana);
	freepolyana(polyana);
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
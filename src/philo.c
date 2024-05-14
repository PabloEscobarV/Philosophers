/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:04:16 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 14:52:27 by blackrider       ###   ########.fr       */
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

int		main()
{
	t_uchar	data;
	t_uchar	bit;

	bit = 32;
	data = 0;
	printf("data: %d\n", data);
	for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
	{
		if (getbit(&data, j))
			printf("%d ", 1);
		else
			printf("%d ", 0);
	}
	printf("\n");
	printf("data: %d\n", data);

	for (int i = 0; i < sizeof(data) * 8; ++i)
	{
		setbit(&data, i);
		for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
		{
			if (getbit(&data, j))
				printf("%d ", 1);
			else
				printf("%d ", 0);
		}
		printf("\n");
	}
	printf("-----------------------------------------\n");
	for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
	{
		if (getbit(&data, j))
			printf("%d ", 1);
		else
			printf("%d ", 0);
	}
	printf("\n");
	printf("-----------------------------------------\n");
	for (int i = 0; i < sizeof(data) * 8; ++i)
	{
		resetbit(&data, i);
		for (int j = sizeof(data) * 8 - 1; j >= 0; --j)
		{
			if (getbit(&data, j))
				printf("%d ", 1);
			else
				printf("%d ", 0);
		}
		printf("\n");
	}
	return (0);
}
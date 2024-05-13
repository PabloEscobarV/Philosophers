/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:04:16 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/13 12:04:26 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

int		main()
{
	t_uchar	data;
	t_uchar	bit;

	bit = 7;
	data = 0;
	for (int i = 0; i < 8; ++i)
	{
		setbit(&data, i);
		for (int j = 7; j >= 0; --j)
		{
			if (getbit(&data, j))
				printf("%d ", 1);
			else
				printf("%d ", 0);
		}
		printf("\n");
	}
	printf("-----------------------------------------\n");
	for (int i = 0; i < 8; ++i)
	{
		resetbit(&data, i);
		for (int j = 7; j >= 0; --j)
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
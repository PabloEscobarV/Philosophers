/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:49:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 13:54:44 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

int	main()
{
	int			count = 10;
	t_times		*times;
	t_polyana	*polyana;

	times = crttimes(1510, 500, 500, 10);
	taskplanner(3, times);
	return (0);
}

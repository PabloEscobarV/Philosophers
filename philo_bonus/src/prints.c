/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:32:56 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/23 15:20:26 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <semaphore.h>

void	printmsg(t_alkash *alkash, const char *msg)
{
	sem_wait(alkash->polyana->semaphrs[OUTSM]);
	printf("%f\t[%d]\t%s\n", tm_sec_f(&alkash->timer), alkash->id, msg);
	sem_post(alkash->polyana->semaphrs[OUTSM]);
}

void	printmsgcolor(t_alkash *alkash, const char *msg, const char *color)
{
	sem_wait(alkash->polyana->semaphrs[OUTSM]);
	printf("%s%f\t[%d]\t%s%s\n", color, tm_sec_f(&alkash->timer),
		alkash->id, msg, RESET_COLOR);
	sem_post(alkash->polyana->semaphrs[OUTSM]);
}
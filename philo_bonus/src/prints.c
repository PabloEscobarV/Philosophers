/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:32:56 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/25 18:27:50 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>
#include <semaphore.h>

void	printmsg(t_alkash *alkash, const char *msg)
{
	printf("%f\t[%d]\t%s\n", tm_sec_f(&alkash->timer), alkash->id, msg);
}

void	printmsgcolor(t_alkash *alkash, const char *msg, const char *color)
{
	printf("%s%f\t[%d]\t%s%s\n", color, tm_sec_f(&alkash->timer),
		alkash->id, msg, RESET_COLOR);
}

void	printmsgdata(t_alkash *alkash, const char *msg, int data)
{
	printf("%f\t[%d]\t%s\t%d\n", tm_sec_f(&alkash->timer), alkash->id, msg,
		data);
}

void	printmsgdatacolor(t_alkash *alkash, const char *msg, const char *color,
		int data)
{
	printf("%s%f\t[%d]\t%s\t%d%s\n", color, tm_sec_f(&alkash->timer),
		alkash->id, msg, data, RESET_COLOR);
}

// sem_wait(alkash->polyana->semaphrs[OUTSM]);
// sem_post(alkash->polyana->semaphrs[OUTSM]);
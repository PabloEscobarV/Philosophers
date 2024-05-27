/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:32:56 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/27 11:36:54 by polenyc          ###   ########.fr       */
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

void	printmsglock(t_alkash *alkash, const char *msg)
{
	sem_wait(alkash->sems[OUTSM]);
	printf("%li\t%d\t%s\n", tm_msec(&alkash->timer), alkash->id, msg);
	sem_post(alkash->sems[OUTSM]);
}

void	printmsglkcolor(t_alkash *alkash, const char *msg, const char *color)
{
	sem_wait(alkash->sems[OUTSM]);
	printf("%s%li\t%d\t%s%s\n", color, tm_msec(&alkash->timer),
		alkash->id, msg, RESET_COLOR);
	sem_post(alkash->sems[OUTSM]);
}

void	printmsgdatacolor(t_alkash *alkash, const char *msg, const char *color,
		int data)
{
	printf("%s%f\t[%d]\t%s\t%d%s\n", color, tm_sec_f(&alkash->timer),
		alkash->id, msg, data, RESET_COLOR);
}

// void	printmsgdata(t_alkash *alkash, const char *msg, int data)
// {
// 	printf("%f\t[%d]\t%s\t%d\n", tm_sec_f(&alkash->timer), alkash->id, msg,
// 		data);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:30 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/15 14:09:35 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"

void	sleep(t_alkash *alkash)
{
    pthread_mutex_lock(&alkash->mutexes[OUT_MT]);
    printf("ALKASH[%d] is sleepling\n");
    pthread_mutex_unlock(&alkash->mutexes[OUT_MT]);
    usleep(alkash->times->sleep_tm * 1000L);
}

void	finding(t_alkash *alkash)
{
    pthread_mutex_lock(&alkash->mutexes[OUT_MT]);
    printf("ALKASH[%d] is finding\n");
    pthread_mutex_unlock(&alkash->mutexes[OUT_MT]);
}

t_uchar	buchat(t_alkash *alkash)
{
	t_timer	cur_tm;

    if (!getbit(alkash->status, PERMITION) ||
        !getbit(alkash->status, IS_LOCKED))
        return (0);
    if (gettimeofday(&cur_tm, NULL))
		printf("ERROR GETTIMEOFDAY!!!\n");
	if (tm_msec(&cur_tm) - tm_msec(&alkash->buchal_tm) > alkash->times->die_tm)
	{
		resetbit(&alkash->status, LIFE_STATUS);
		return (0);
	}
}
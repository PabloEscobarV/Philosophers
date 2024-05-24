/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:31 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/24 16:35:58 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int	correcti(t_alkash *alkash)
{
	int	i;

	i = alkash->id + 1;
	if (i >= alkash->polyana->count)
		return (0);
	return (i);
}

t_uchar	setdead(t_alkash *alkash)
{
	if (sem_wait(alkash->sems[LIFESM]))
		return (SEMERROR);
	resetbit(&alkash->lifestate, LIFE_STATUS);
	if (sem_post(alkash->sems[LIFESM]))
		return (SEMERROR);
	return (DEAD);
}

t_uchar	increaslock(t_alkash *alkash)
{
	if (sem_wait(alkash->sems[NUMBUCHTM]))
		return (SEMERROR);
	++alkash->numbuch;
	if (sem_post(alkash->sems[NUMBUCHTM]))
		return (SEMERROR);
	return (DEAD);
}

// void	sighandler(int signum, siginfo_t *si, void *unctx)
// {
// 	printf("SIGHADLER!!!!\n");
// 	if (signum == SIGINT || signum == SIGTERM)
// 		exit(SIGINT);
// }

// void setup_signal_handler()
// {
// 	struct sigaction	*sa;

// 	sa = malloc(sizeof(struct sigaction));
// 	sa->sa_sigaction = sighandler;
// 	sa->sa_flags = SA_SIGINFO;
// 	sigaddset(&sa->sa_mask, SIGTERM);
// 	sigaddset(&sa->sa_mask, SIGINT);
// 	if (sigaction(SIGINT, sa, NULL) < 0)
// 		return ;
// 	if (sigaction(SIGTERM, sa, NULL) < 0)
// 		return ;
// }

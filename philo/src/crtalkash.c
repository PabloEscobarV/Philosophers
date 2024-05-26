/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crtalkash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:05:00 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 21:08:28 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdlib.h>

t_alkash	*crtalkash(int id, t_polyana *polyana)
{
	t_alkash	*alkash;

	alkash = malloc(sizeof(t_alkash));
	if (!alkash)
		return (NULL);
	alkash->numbuch = 0;
	alkash->cmnstate = 0;
	alkash->status = 0;
	alkash->tm_dead = 0;
	alkash->id = id;
	alkash->polyana = polyana;
	setbit(&alkash->cmnstate, LIFE_STATUS);
	if (id % 2)
		setbit(&alkash->cmnstate, PERMITION);
	gettimeofday(&alkash->timer, NULL);
	alkash->buchal_tm = alkash->timer;
	return (alkash);
}

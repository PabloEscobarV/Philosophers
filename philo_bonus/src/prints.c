/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:32:56 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 16:08:07 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philo.h"
#include <stdio.h>

void	printmsg(t_alkash *alkash, const char *msg)
{
	printf("%f\t[%d]\t%s\n", tm_sec_f(&alkash->timer), alkash->id, msg);
}

void    printstatus(t_polyana *polyana)
{

}
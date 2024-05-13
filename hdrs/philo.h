/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/13 11:50:32 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#define BIT_MAX			7
#define	MAXBITNUMBER	255

typedef unsigned char	t_uchar;

enum
{
	PERMITION,
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEPING,
	IS_FIDING,
}

typedef struct	s_alkashi
{
	t_uchar		status;
}				t_alkashi;

typedef struct	s_polyna
{
	t_uchar		*buchlo;
	t_alkash	*alkashi;
}				t_polyna;

///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar	setbit(t_uchar *data, t_uchar bit);
t_uchar	resetbit(t_uchar *data, t_uchar bit);
t_uchar	getbit(t_uchar *data, t_uchar bit);
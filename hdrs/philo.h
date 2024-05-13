/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/13 12:18:16 by polenyc          ###   ########.fr       */
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
	ERROR,
	PERMITION,
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEPING,
	IS_FIDING,
};

typedef struct	s_alkash
{
	t_uchar		status;
}				t_alkash;

typedef struct	s_polyna
{
	t_uchar		*buchlo;
	t_alkash	*alkashi;
}				t_polyna;

///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar	setbit(t_uchar *data, t_uchar bit);
t_uchar	resetbit(t_uchar *data, t_uchar bit);
t_uchar	getbit(t_uchar *data, t_uchar bit);
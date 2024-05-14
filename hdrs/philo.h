/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 13:17:14 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
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

typedef struct timeval t_timer;

typedef struct	s_alkash
{
	t_timer		timer;
	t_uchar		status;
}				t_alkash;

typedef struct	s_polyna
{
	int			count;
	long		buchat_tm;
	long		die_tm;
	long		sleep_tm;
	t_uchar		*buchlo;
	t_alkash	*alkashi;
}				t_polyna;

///////////////////////////////POLYANA/////////////////////////////
t_polyna	*crtpolyana(int count, long buchat_tm, long sleep_tm, long die_tm);
void		*freepolyana(t_polyna *polyana);
///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar *data, t_uchar bit);
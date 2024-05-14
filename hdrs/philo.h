/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/14 14:51:38 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#define BIT_MAX			8
#define	MAXBITNUMBER	255

typedef unsigned char	t_uchar;

enum
{
	ERROR,
	MEMMORY_ERROR,
	PERMITION,
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEPING,
	IS_FIDING,
	PTHREADCRT_ERROR,
	PTHREADJOIN_ERROR
};

typedef struct timeval t_timer;

typedef struct s_times
{
	int			nofepme;
	long		buchat_tm;
	long		die_tm;
	long		sleep_tm;
}				t_times;

typedef struct	s_alkash
{
	t_timer		timer;
	t_uchar		status;
}				t_alkash;

typedef struct	s_polyna
{
	int			count;
	int			status;
	t_times		*times;
	t_uchar		*buchlo;
	t_alkash	*alkashi;
	pthread_t	*threads;
}				t_polyana;

///////////////////////////////POLYANA/////////////////////////////
t_polyana	*crtpolyana(int count, t_times *times);
void		*freepolyana(t_polyana *polyana);
t_times		*crttimes(long buchat_tm, long sleep_tm, long die_tm, int nofepme);
///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar *data, t_uchar bit);
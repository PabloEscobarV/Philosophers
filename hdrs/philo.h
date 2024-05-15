/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/15 11:33:06 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#define BIT_MAX			8
#define	MAXBITNUMBER	255

typedef unsigned char	t_uchar;

enum
{
	LIFE_STATUS,
	PERMITION,
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEPING,
	IS_FIDING,
	ERROR,
};

enum
{
	ERROR_THCRT,
	ERROR_THJOIN,
};

enum
{
	OUT_MT,
	PLANNER_MT,
	MUTEX_COUNT
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
	int				id;
	int				count;
	t_uchar			status;
	t_timer			timer;
	t_uchar			*buchlo;
	pthread_mutex_t	*mutexes;
	t_times			*times;
	struct s_alkash	**alkashi;
}				t_alkash;

typedef struct	s_polyna
{
	t_uchar			status;
	int				count;
	pthread_mutex_t	*mutexes;
	pthread_t		*threads;
	t_times			*times;
	t_uchar			*buchlo;
	t_alkash		**alkashi;
}					t_polyana;

///////////////////////////////POLYANA/////////////////////////////
t_polyana	*crtpolyana(int count, t_times *times);
void		*freepolyana(t_polyana *polyana);
t_times		*crttimes(long buchat_tm, long sleep_tm, long die_tm, int nofepme);
t_alkash	*crtalkash(int id, t_polyana *polyana);
///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar *data, t_uchar bit);
///////////////////////////////TIMER/////////////////////////////
long		tm_usec(t_alkash *alkash);
long		tm_msec(t_alkash *alkash);
long		tm_sec(t_alkash *alkash);
float		tm_sec_f(t_alkash *alkash);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/15 16:11:27 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#define BIT_MAX			8
#define	MAXBITNUMBER	255
#define CHECKTIME		2

typedef unsigned char	t_uchar;

enum
{
	LIFE_STATUS,
	PERMITION,
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEPING,
	IS_FIDING,
	ERROR
};

enum
{
	IS_DEAD,
	ERROR_THCRT,
	ERROR_THJOIN,
};

enum
{
	OUT_MT,
	CHECK_MT,
	GET_MT,
	PLANNER_MT,
	MUTEX_COUNT
};

typedef struct timeval t_timer;
typedef struct	s_polyna t_polyana;

typedef struct s_times
{
	int			nofepme;
	long		buchat_tm;
	long		die_tm;
	long		sleep_tm;
}				t_times;

typedef struct	s_alkash
{
	t_uchar			status;
	int				id;
	t_timer			buchal_tm;
	t_timer			timer;
	t_polyana		*polyana;
}				t_alkash;

struct	s_polyna
{
	t_uchar			status;
	int				count;
	long			lastcheck;
	pthread_mutex_t	*mutexes;
	pthread_t		*threads;
	t_times			*times;
	t_uchar			*buchlo;
	t_alkash		**alkashi;
};

///////////////////////////////POLYANA/////////////////////////////
t_polyana	*crtpolyana(int count, t_times *times);
void		*freepolyana(t_polyana *polyana);
t_times		*crttimes(long buchat_tm, long sleep_tm, long die_tm, int nofepme);
t_alkash	*crtalkash(int id, t_polyana *polyana);
///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar data, t_uchar bit);
///////////////////////////////TIMER/////////////////////////////
long		tm_usec(const t_timer *timer);
long		tm_msec(const t_timer *timer);
long		tm_sec(const t_timer *timer);
float		tm_sec_f(const t_timer *timer);
///////////////////////////////ACTIONS/////////////////////////////
void		finding(t_alkash *alkash);
void		a_sleep(t_alkash *alkash);
t_uchar		getbuchlo(t_alkash *alkash);
void		putbuchlo(t_alkash *alkash);
t_uchar		buchat(t_alkash *alkash);
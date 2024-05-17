/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/17 09:27:54 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#define BIT_MAX			8
#define	MAXBITNUMBER	255
#define CHECKTIME		5
#define BUCHLO_LOCK		1
#define METRICS			1000L
#define EXECTIME		20

typedef unsigned char	t_uchar;

enum
{
	LIFE_STATUS,
	PERMITION,
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEEPING,
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
	SETST_MT,
	GETBUCHLO_MT,
	PUTBUCHLO_MT,
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
	float			tm_dead;
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

t_uchar		taskplanner(int count, t_times *times);
///////////////////////////////PRINT/////////////////////////////
void		printmsg(t_alkash *alkash, const char *msg);
void		printstatus(t_alkash *alkash);
void		print(t_alkash *alkash);
///////////////////////////////POLYANA/////////////////////////////
t_polyana	*crtpolyana(int count, t_times *times);
void		*freepolyana(t_polyana *polyana);
t_times		*crttimes(long buchat_tm, long sleep_tm, long die_tm, int nofepme);
t_alkash	*crtalkash(int id, t_polyana *polyana);
///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar data, t_uchar bit);
t_uchar		setbitlock(t_alkash *alkash, t_uchar bit);
t_uchar		resetbitlock(t_alkash *alkash, t_uchar bit);
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
///////////////////////////////TOOLS/////////////////////////////
int			correcti(t_alkash *alkash);
void		setdead(t_alkash *alkash);


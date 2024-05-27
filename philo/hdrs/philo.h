/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/27 11:26:42 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <pthread.h>
#include <sys/time.h>
#define BIT_MAX			8
#define MAXBITNUMBER	255
#define CHECKTIME		2
#define BUCHLO_LOCK		1
#define METRICS			1000L
#define EXECTIME		20
#define RESET_COLOR		"\033[0m"
#define RED				"\033[31m"
#define GREEN			"\033[32m"
#define YELLOW			"\033[33m"
#define BLUE			"\033[34m"
#define MAGENTA			"\033[35m"
#define CYAN			"\033[36m"
#define WHITE			"\033[37m"
#define GETBUCHLOMSG	"has taken a fork"
#define BUCHATMSG		"is eating"
#define SLEEPINGMSG		"is sleeping"
#define FINDINGMSG		"is thinking"
#define DEATHMSG		"is died"
#define NUMBUCHTMMSG	"NUMBER OF TIMES EACH PHILOSOPHER ATE"

typedef unsigned char	t_uchar;

enum e_COMMON
{
	LIFE_STATUS,
	PERMITION,
	OVERNUMBUCHAT,
};

enum e_LOCAL
{
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEEPING,
	IS_FIDING,
	ERROR
};

enum e_POLYANA_STATE
{
	IS_DEAD,
	ERROR_THCRT,
	ERROR_THJOIN,
};

enum e_MUTEXES
{
	OUT_MT,
	CHECK_MT,
	STTS_MT,
	DEAD_MT,
	BUCHLO_MT,
	COUNTER_MT,
	TIME_MT,
	MUTEX_COUNT,
};

typedef struct timeval	t_timer;
typedef struct s_polyna	t_polyana;

typedef struct s_times
{
	int			nofepme;
	long		buchat_tm;
	long		die_tm;
	long		sleep_tm;
}				t_times;

typedef struct s_alkash
{
	t_uchar			cmnstate;
	t_uchar			status;
	int				id;
	int				numbuch;
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
	pthread_mutex_t	*mts;
	pthread_t		*threads;
	t_times			*times;
	t_timer			timer;
	t_uchar			*buchlo;
	t_alkash		**alkashi;
};

t_uchar		taskplanner(int count, t_times *times);
///////////////////////////////CHECK`S/////////////////////////////
t_uchar		checkalkashi(t_alkash *alkash);
void		*checkpolyana(void *polyana);
///////////////////////////////PRINT/////////////////////////////
void		printmsg(t_alkash *alkash, const char *msg, const char *color);
void		printstatus(t_polyana *polyana, const char *msg);
void		printbits(t_alkash *alkash);
void		printdead(t_alkash *alkash);
void		printdeadlk(t_alkash *alkash);
///////////////////////////////POLYANA/////////////////////////////
t_polyana	*crtpolyana(int count, t_times *times);
void		*freepolyana(t_polyana *polyana);
///////////////////////////////ALKASH/////////////////////////////
t_alkash	*crtalkash(int id, t_polyana *polyana);
///////////////////////////////TIMES/////////////////////////////
t_times		*crttimes(long die_tm, long buchat_tm, long sleep_tm, int nofepme);
int			cornum(const char *data);
///////////////////////////////BIT OPERATIONS/////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar *data, t_uchar bit);
void		setbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex);
void		resetbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex);
t_uchar		getbitlock(t_uchar *data, t_uchar bit, pthread_mutex_t *mutex);
///////////////////////////////TIMER/////////////////////////////
long		tm_usec(const t_timer *timer);
long		tm_msec(const t_timer *timer);
long		tm_sec(const t_timer *timer);
float		tm_sec_f(const t_timer *timer);
void		setmbuchal_tm(t_alkash *alkash);
///////////////////////////////ACTIONS/////////////////////////////
void		finding(t_alkash *alkash);
void		a_sleep(t_alkash *alkash);
t_uchar		getbuchlo(t_alkash *alkash);
void		putbuchlo(t_alkash *alkash);
t_uchar		buchat(t_alkash *alkash);
///////////////////////////////TOOLS/////////////////////////////
int			correcti(t_alkash *alkash);
void		setdead(t_alkash *alkash);
void		setdeadlk(t_alkash *alkash);
void		increascounter(t_alkash *alkash);
long		ft_atoi(const char *nptr);

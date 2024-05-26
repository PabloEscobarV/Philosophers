/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/26 20:52:33 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <semaphore.h>
#include <sys/time.h>

#define BIT_MAX			8
#define METRICS			1000L
#define CHECKTIME		5L
#define SEMERROR		0
#define DEAD			1
#define PERMNAME		"PERMITION."
#define SEMSNAME		"SEMAPHORES."
#define SEMSLCNAME		"SEMAPHORESLOCAL."
#define BUCHLONAME		"BUCHLO"
#define STATESM			"STATESM"
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

typedef unsigned char		t_uchar;
typedef struct timeval		t_timer;
typedef struct s_polyana	t_polyana;

enum	e_localstate
{
	IS_LOCKED,
	IS_BUCHING,
	IS_SLEEPING,
	IS_FIDING,
	ERROR = 7
};

enum	e_cmnsemaphores
{
	DEATHSM,
	COUNTSM,
};

enum	e_localsems
{
	OUTSM,
	NUMBUCHTMSM,
	TIMESM,
	COUNTLOCALSM,
};

typedef struct s_times
{
	int			nofepme;
	long		buchat_tm;
	long		die_tm;
	long		sleep_tm;
}				t_times;

typedef struct s_alkash
{
	t_uchar		state;
	int			id;
	int			numbuch;
	t_timer		lastbuchtm;
	t_timer		timer;
	t_polyana	*polyana;
	char		**semnames;
	sem_t		**sems;
}				t_alkash;

typedef struct s_polyana
{
	int		count;
	int		count_edev;
	pid_t	*pids;
	t_times	*times;
	char	**permname;
	char	**cmnsemsname;
	sem_t	*buchlo_sm;
	sem_t	**perm_sm;
	sem_t	**cmnsems;
}			t_polyana;

t_uchar		taskplanner(t_polyana *polyana);
/////////////////////////////////////CHECKER//////////////////////////////////
void		*checker(void *data);
void		*deathcontrol(void *data);
/////////////////////////////////////CRT POLYANA//////////////////////////////
t_times		*crttimes(long die_tm, long buchat_tm, long sleep_tm, int nofepme);
t_polyana	*crtpolyana(int count, int cnt_dev, t_times *times);
t_alkash	*crtalkash(int id, t_polyana *polyana);
char		**crtname(int count, const char *name);
/////////////////////////////////////CRT POLYANA///////////////////////////////
sem_t		*crtsemaphor(const char *name, int val);
sem_t		**crtpermsem(int count, const char **names);
sem_t		**crtsemaphores(int count, const char **names);
/////////////////////////////////////ACTIONS///////////////////////////////////
t_uchar		getbuchlo(t_alkash	*alkash);
t_uchar		buchat(t_alkash *alkash);
void		putbuchlo(t_alkash *alkash);
void		a_sleep(t_alkash *alkash);
void		finding(t_alkash *alkash);
/////////////////////////////////////TOOLS/////////////////////////////////////
char		*ft_strjoinfree(char *s1, char *s2, int pos);
char		*ft_itoa(int n);
int			correcti(t_alkash *alkash);
t_uchar		setdead(t_alkash *alkash);
t_uchar		increaslock(t_alkash *alkash);
long		ft_atoi(const char *nptr);
/////////////////////////////////////FREE FUNC/////////////////////////////////
void		*freepolyana(t_polyana *polyana);
void		*freesem(int count, const char **names);
void		*freename(char **names);
void		*freealkash(t_alkash *alkash);
void		freealkashsems(t_alkash *alkash);
/////////////////////////////////////TIMER/////////////////////////////////////
long		tm_usec(const t_timer *timer);
long		tm_msec(const t_timer *timer);
long		tm_sec(const t_timer *timer);
float		tm_sec_f(const t_timer *timer);
void		setlastbuchtmlock(t_alkash *alkash);
/////////////////////////////////////PRINTS/////////////////////////////////////
void		printmsg(t_alkash *alkash, const char *msg);
void		printmsgcolor(t_alkash *alkash, const char *msg, const char *color);
void		printmsglock(t_alkash *alkash, const char *msg);
void		printmsglkcolor(t_alkash *alkash, const char *msg, const char *col);
void		printmsgdatacolor(t_alkash *alkash, const char *msg,
				const char *color, int data);
/////////////////////////////////////BIT OPERATION//////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar *data, t_uchar bit);
t_uchar		setbitlock(t_uchar *data, t_uchar bit, sem_t *sem);
t_uchar		resetbitlock(t_uchar *data, t_uchar bit, sem_t *sem);
t_uchar		getbitlock(t_uchar *data, t_uchar bit, sem_t *sem);

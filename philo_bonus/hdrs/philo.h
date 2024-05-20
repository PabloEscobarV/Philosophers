/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 16:52:51 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <semaphore.h>
#include <sys/time.h>

#define BIT_MAX	8
#define METRICS	1000L

typedef unsigned char		t_uchar;
typedef struct timeval		t_timer;
typedef struct s_polyana	t_polyana;

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

typedef struct s_times
{
	int			nofepme;
	long		buchat_tm;
	long		die_tm;
	long		sleep_tm;
}				t_times;

typedef struct	s_alkash
{
	t_uchar		state;
	int			id;
	t_timer		lastbuchtm;
	t_timer		timer;
	t_polyana	*polyana;
}				t_alkash;


typedef struct s_polyana
{
	int		count;
	int		count_edev;
	char	**buchloname;
	char	**permname;
	t_times	*times;
	sem_t	*out_sem;
	sem_t	*buchlo;
	sem_t	**permition;
}			t_polyana;

/////////////////////////////////////CRT POLYANA/////////////////////////////////////
t_times		*crttimes(long die_tm, long buchat_tm, long sleep_tm, int nofepme);
t_polyana   *crtpolyana(int count, t_times *times);
t_alkash	*crtalkash(int id, t_polyana *polyana);
/////////////////////////////////////ACTIONS/////////////////////////////////////
void		getbuchlo(t_alkash	*alkash);
t_uchar		buchat(t_alkash *alkash);
void		a_sleep(t_alkash *alkash);
void		finding(t_alkash *alkash);
/////////////////////////////////////TOOLS/////////////////////////////////////
char		*ft_strjoinfree(char *s1, char *s2, int pos);
char		*ft_itoa(int n);
/////////////////////////////////////FREE FUNC/////////////////////////////////////
void		*freepolyana(t_polyana *polyana);
void		*freesem(int count, const char **names);
void		*freename(char **names);
/////////////////////////////////////TIMER/////////////////////////////////////
long		tm_usec(const t_timer *timer);
long		tm_msec(const t_timer *timer);
long		tm_sec(const t_timer *timer);
float		tm_sec_f(const t_timer *timer);
/////////////////////////////////////PRINTS/////////////////////////////////////
void		printmsg(t_alkash *alkash, const char *msg);
/////////////////////////////////////BIT OPERATION/////////////////////////////////////
t_uchar		setbit(t_uchar *data, t_uchar bit);
t_uchar		resetbit(t_uchar *data, t_uchar bit);
t_uchar		getbit(t_uchar *data, t_uchar bit);

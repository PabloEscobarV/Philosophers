/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:15:10 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 14:03:46 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <semaphore.h>
#include <sys/time.h>

typedef struct timeval	t_timer;

typedef struct s_times
{
	int			nofepme;
	long		buchat_tm;
	long		die_tm;
	long		sleep_tm;
}				t_times;

typedef struct s_polyana
{
	int		count;
	t_timer	timer;
	char	**buchloname;
	char	**permname;
	t_times	*times;
	sem_t	**buchlo;
	sem_t	**permition;
}				t_polyana;

/////////////////////////////////////CRT POLYANA/////////////////////////////////////
t_times		*crttimes(long die_tm, long buchat_tm, long sleep_tm, int nofepme);
t_polyana   *crtpolyana(int count, t_times *times);
/////////////////////////////////////TOOLS/////////////////////////////////////
char		*ft_strjoinfree(char *s1, char *s2, int pos);
char		*ft_itoa(int n);
/////////////////////////////////////FREE FUNC/////////////////////////////////////
void		*freepolyana(t_polyana *polyana);
void		*freesem(int count, const char **names);
void		*freename(char **names);

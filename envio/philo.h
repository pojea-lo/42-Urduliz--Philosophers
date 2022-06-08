/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:56:20 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/05/30 18:38:16 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include <sys/time.h>

//data input structure
typedef struct s_dat
{
	int				i;
	int				j;
	int				k;
	int				nph;
	int				*fork;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mspf;
	pthread_mutex_t	dead;
	int				spf;
	int				sd;
	int				impi;
	int				impp;
	long			td;
	long			te;
	long			ts;
	int				*ne;
	long			tstart;
	long			tthink;

}	t_dat;

typedef struct s_sphilo
{
	int			id;
	long		lte;
	long		lts;
	int			sp;
	int			se;
	int			sem;
	int			sw;
	int			ss;
	t_dat		*in;

}	t_sphilo;
/*
typedef struct s_thread
{
	pthread_t	*t;
}	t_thread;
*/
//philo. (main)c
int			ft_start(t_dat *in);
int			ft_start_two(pthread_t *t, t_sphilo **phil);
t_sphilo	*ft_data(int i, t_dat *in);

//philo_utils_0.c
int			ft_argm_input(int argc, char *argv[], t_dat *in);
int			ft_argm_control(t_dat *in);
int			ft_atoi(char *str);
void		ft_free_in(t_dat *in);
void		ft_free_phil(t_sphilo **phil, pthread_t *t);

//philo_utils_1.c
void		ft_printf(int i, t_sphilo *phil);
int			ft_check(t_sphilo *phil);
int			ft_check_moment(t_sphilo *phil);
long		ft_time(long tstart);
int			ft_usleep(long time, t_sphilo *phil);

//philo_utils_2.c
int			ft_eat(t_sphilo *phil);
int			ft_eat_last(t_sphilo *phil);
int			ft_sleep(t_sphilo *phil);
int			ft_think(t_sphilo *phil);

//philo_utils_3.c
void		*ft_create(void *phil_anterior);
int			ft_create_aux(t_sphilo *phil);
int			ft_take(t_sphilo *phil);
int			ft_take_rest(t_sphilo *phil);
int			ft_take_last(t_sphilo *phil);

#endif

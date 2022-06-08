/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 07:55:49 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/06/07 07:55:51 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

//data input structure
typedef struct s_dat
{
	int				i;
	int				nph;
	int				id;
	int				group;
	int				fork;
	sem_t			*mspf;
	sem_t			*died;
	sem_t			*semfork;
	int				spf;
	int				sd;
	long			td;
	long			te;
	long			ts;
	int				ne;
	long			tstart;
	long			tthink;
	long			lte;
	long			lts;
	int				sp;
	int				se;
	int				sem;
	int				sw;
	int				ss;

}	t_dat;

//bonus_philo.c (main)c
int			ft_start(t_dat *in);
int			ft_start_two(pid_t *pid, t_dat *in);
void		ft_kill(t_dat *in, pid_t *pid);

//bonus_philo_utils_0.c
int			ft_argm_input(int argc, char *argv[], t_dat *in);
int			ft_argm_control(t_dat *in);
int			ft_atoi(char *str);

//bonus_philo_utils_1.c
int			ft_printf(int i, t_dat *in);
int			ft_check(t_dat *in);
int			ft_check_moment(t_dat *in);
long		ft_time(long tstart);
int			ft_usleep(long time, t_dat *in);

//bonus_philo_utils_2.c
int			ft_eat(t_dat *in);
int			ft_eat_last(t_dat *in);
int			ft_sleep(t_dat *in);
int			ft_think(t_dat *in);

//bonus_philo_utils_3.c
int			ft_create(t_dat *in);//, int id);
int			ft_group(t_dat *in);
int			ft_create_aux(t_dat *in);
int			ft_take(t_dat *in);
int			ft_take_rest(t_dat *in);
int			ft_take_last(t_dat *in);

#endif

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

//data input structure
typedef struct	s_dat
{
	int		nph;//numero de filosofos
	int		nfk;//numero de tenedors
	int		td;//tiempo para morir
	int		te;//tiempo para comer
	int		ts;//tiempo para dormir
	int		ne;//numero de commidas necesarias
}	t_dat;

//pthread structure
typedef struct	s_thread
{
	pthread_t	*t;
}	t_thread;

//philo.c
int			ft_start (t_dat *in);
void		*ft_eat();
long int	ft_time();

//philo_utils_0.c
int		ft_argm_input (int argc, char *argv[], t_dat *in);
int		ft_argm_control (t_dat *in);
int		ft_atoi (char *str);


#endif


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
	int			i;//contador 1
	int			j;//contador 2
	int			nph;//numero de filosofos
	int			*nfk;//array con numero de tenedores 0 libre / 1 ocupado
	double		td;//tiempo para morir
	double		te;//tiempo para comer
	double		ts;//tiempo para dormir
	int			ne;//numero de commidas necesarias
	double		tstart;//tiempo de inicio del programa
	double		tfinal;//tiempo de remate del programa
	double		tthink;//tiempo de pensar

	pthread_mutex_t	mutex_1;//bloqueo de filosofos pares
}	t_dat;

typedef struct	s_sphilo//estructura para cada filosofo
{
	int			id;//numero identificador del filosofo
	int			sfork;//0 si esta libre 1 si esta ocupado
	double		lte;//tiempos de empezar a comer
	double		lts;//tiempos de empezar a dormir
	t_dat		in;
}	t_sphilo;

//pthread structure
typedef struct	s_thread
{
	pthread_t	*t;
}	t_thread;

//philo.c
int			ft_start_select (t_dat *in);
int			ft_par_start (t_dat *in);
void		*ft_create();
double		ft_time(double tstart);

//philo_utils_0.c
int		ft_argm_input (int argc, char *argv[], t_dat *in);
int		ft_argm_control (t_dat *in);
int		ft_atoi (char *str);
void	ft_free (t_dat *in);

#endif

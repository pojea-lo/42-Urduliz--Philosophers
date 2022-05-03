#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include <sys/time.h>

//data input structure
typedef struct	s_dat
{
	int				i;//contador 1
	int				j;//contador 2
	int				k;//contador 3
	int				nph;//numero de filosofos
	int				*fork;//array estado tenedores, 0 libre / 1 ocupado
	pthread_mutex_t	*mutex;//array de mutex para tenedores
	double			td;//tiempo para morir
	double			te;//tiempo para comer
	double			ts;//tiempo para dormir
	int				*ne;//numero de commidas necesarias
	double			tstart;//tiempo de inicio del programa
	int				tfinal;//tiempo de remate del programa
	double			tthink;//tiempo de pensar

}	t_dat;

typedef struct	s_sphilo//estructura para cada filosofo
{
	int			id;//numero identificador del filosofo
	double		lte;//tiempos de empezar a comer
	double		lts;//tiempos de inicio de la ultima comida
	int			sp;//estado de primera pasada para la primera condicion de muerte
	int			se;//estado si ha comido, 0 si no / 1 si si
	int			ss;//estado si ha dormido, 0 si no / 1 si si
	t_dat		*in;

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
int			ft_take(t_sphilo *phil);
int			ft_eat(t_sphilo *phil);
int			ft_sleep(t_sphilo *phil);
int			ft_think(t_sphilo *phil);
int			ft_check(t_sphilo *phil);
void		ft_usleep(double time, double tstart);
double		ft_time(double tstart);

//philo_utils_0.c
int		ft_argm_input (int argc, char *argv[], t_dat *in);
int		ft_argm_control (t_dat *in);
int		ft_atoi (char *str);
void	ft_free (t_dat *in);

#endif

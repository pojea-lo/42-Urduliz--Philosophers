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
	pthread_t		died;//hilo para la muerte
	pthread_mutex_t	mspf;//mutex para la impresion 0 se puede imprimir / 1 no
	int				spf;//mutex para la impresion 0 se puede imprimir / 1 no
	int				sd;//estado de muerte 2 vivo / 1 muerto
	long			td;//tiempo para morir
	long			te;//tiempo para comer
	long			ts;//tiempo para dormir
	int				*ne;//numero de commidas necesarias
	long			tstart;//tiempo de inicio del programa
	long			tthink;//tiempo de pensar

}	t_dat;

typedef struct	s_sphilo//estructura para cada filosofo
{
	int			id;//numero identificador del filosofo
	long		lte;//tiempos de empezar a comer
	long		lts;//tiempos de inicio de la ultima comida
	int			sp;//estado de primera pasada para la primera condicion de muerte
	int			se;//estado si ha comido, 0 si no / 1 si si
	int			sem;//estado si ha comido la primera vez, 0 si no / 1 si si
	int			sw;//estado si ha esperado la primera vez o no, 0 si no / 1 si si
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
int			ft_ant (t_dat *in);
int			ft_start (t_dat *in);
t_sphilo	*ft_data (int i, t_dat *in);
void		*ft_create();
int			ft_take(t_sphilo *phil);
int			ft_eat(t_sphilo *phil);
int			ft_eat_last(t_sphilo *phil);
int			ft_sleep(t_sphilo *phil);
int			ft_think(t_sphilo *phil);
int			ft_check(t_sphilo *phil);
int			ft_check_moment(t_sphilo *phil);
int			ft_usleep(long time, t_sphilo *phil);
long		ft_time(long tstart);

//philo_utils_0.c - funciones para entrada de datos y liberación
int		ft_argm_input (int argc, char *argv[], t_dat *in);
int		ft_argm_control (t_dat *in);
int		ft_atoi (char *str);
void	ft_free_in (t_dat *in);
void	ft_free_phil (t_sphilo **phil, pthread_t *t);

//philo_utils_1.c - funciones para entrada de datos y liberación
void	ft_printf(int i, t_sphilo *phil);

#endif

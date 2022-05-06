#include "philo.h"

int	main(int argc, char *argv[])
{
	t_dat	in;

	if (argc != 5 && argc != 6)
	{
		write (1, "Number of arguments error\n", 26);
		return (1);
	}
	if (ft_argm_input (argc, argv, &in) == 1)
		return (1);
	in.tthink = 0;//in.td - (in.te + in.ts + 0.013);//margen de 13ml para realizar todo un proceso entero de filosofo (son unos 11ms como máximo)  
	if (in.tthink < 0)//hay casos que da negativo y no han de morir 4 410 200 200 pej.
		in.tthink = 0;
	in.tstart = 0;
	in.tstart = ft_time(in.tstart);
	in.fork = (int *) malloc (sizeof(int) * (in.nph + 1));//malloc con +1 para el tenedor del ultimo filosofo
	in.mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
	if (in.fork == NULL || in.mutex == NULL)
		return (1);//HAY QUE LIBERAR**
	if (ft_ant (&in) == 1)
		return (1);//HAY QUE LIBERAR**
//	if (ft_start (&in) == 1)
//		return (1);//HAY QUE LIBERAR**
	free (in.fork);
	free (in.ne);
	return(0);
}

int	ft_ant (t_dat *in)//funcion que crea el hilo principal de muerte
{
	pthread_mutex_init (&in->mdied, NULL);//inicio el mutex de la muerte
	if (pthread_create (&in->died, NULL, &ft_start, in) != 0)//creo el hilo ppal de muerte
	{
		write (1,"Create pthread error\n", 21);
		return (1);//HAY QUE LIBERAR**
	}
	pthread_join (in->died, NULL);
	pthread_mutex_destroy (&in->mdied);
	return (0);
}

void	*ft_start (t_dat *in)//funcion que crea y destruye los hilos
{
	pthread_t		t[in->nph];
	t_sphilo		*phil;

	pthread_mutex_lock (&in->mdied);
	in->i = -1;
	while (++in->i < in->nph)
	{
		phil = NULL;
		phil = (t_sphilo *) malloc (sizeof(t_sphilo));//proteger malloc
		ft_data (phil, in);
		pthread_mutex_init (&phil->in->mutex[in->i], NULL);//inicio los mutex
		if (pthread_create (&t[in->i], NULL, &ft_create, phil) != 0)//creo los hilos
		{
			write (1,"Create pthread error\n", 21);
			return ((void *) 1);//HAY QUE LIBERAR**
		}
	}
	in->j = -1;
	while (++in->j < in->nph)
	{
		pthread_join (t[in->j], (void **) &phil);
		pthread_mutex_destroy (&phil->in->mutex[in->j]);
//		free (&phil->in->mutex[in->j]);
//		free (phil);
	}
	return (0);
}

void	ft_data(t_sphilo *phil, t_dat *in)//carga datos iniciales a las variables de la estructura del filo
{
	phil->in = in;//cargo la estructura in dentro de la phil
	phil->id = in->i;//añado el id de todos los filosofos
	in->fork[in->i] = 0;//pongo a cero todos los tenedores
	if (in->i == 0 && in->nph > 1)//pongo a cero el tenedor para el utlimo filosofo
		in->fork[in->nph] = in->fork[in->i];
	phil->sp = 0;//estado de primera pasada
	phil->se = 0;//estado de comidas
	phil->ss = 0;//estado de dormidas
	phil->in->sd = 2;//estado de muerte (pongo 2 para que imprima solo 1 died)
}

void	*ft_create(t_sphilo *phil)//funcion que retiene los hilos
{
	pthread_mutex_unlock (&phil->in->mdied);
	while (phil->in->sd == 2)//bucle infinito para retener los hilos DA SEGF si compilo sin SAN!!! 
	{
		if (phil->id % 2 == 0)//empiezan comiendo los impares (id+1 por el filosofo 0)
		{
			if (ft_take (phil) == 1)
			{	
	//			pthread_mutex_unlock (&phil->in->died);
				return ((void *)1);
			}
		}
		else
		{
			usleep (50);//pequeño retardo para los filosofos pares y no se atropellen entre todos
			if (ft_take (phil) == 1)
			{	
	//			pthread_mutex_unlock (&phil->in->died);
				return ((void *)1);
			}
		}
		if (phil->in->ne[phil->id] == 0)
			break;
	}
	return (0);
}

int		ft_take(t_sphilo *phil)//funcion para coger los tenedores
{
	while (phil->in->fork[phil->id] == 0 && phil->in->fork[phil->id + 1] == 0 && phil->in->ne[phil->id] != 0 && phil->se == 0 && phil->in->sd == 2)
	{
		if (phil->in->fork[phil->id] == 0 && phil->in->fork[(phil->id) + 1] == 0 && phil->in->sd == 2)
		{
			pthread_mutex_lock (&phil->in->mutex[phil->id]);
			pthread_mutex_lock (&phil->in->mutex[phil->id + 1]);
			phil->in->fork[phil->id] = 1;
			phil->in->fork[(phil->id) + 1] = 1;
			ft_printf (1, phil);
			ft_printf (1, phil);
		}
		if (ft_eat(phil) == 1)
			return (1);
	}
	if (phil->in->sd == 2)
		ft_sleep(phil);
	if (phil->in->sd == 2)
		ft_think(phil);
	return (0);
}

int		ft_eat(t_sphilo *phil)//funcion de comer
{
	if (phil->in->fork[phil->id] == 1 && phil->in->fork[phil->id + 1] == 1)
	{
		phil->lts = phil->lte;
		phil->lte = ft_time(phil->in->tstart);
		if (ft_check (phil) == 1)
			return (1);
		ft_printf (2, phil); 
//		usleep (phil->in->te * 1e3);
		ft_usleep (phil->in->te, phil->in->tstart, phil->in->sd);
		pthread_mutex_unlock (&phil->in->mutex[phil->id]);
		pthread_mutex_unlock (&phil->in->mutex[phil->id + 1]);
		phil->in->fork[phil->id] = 0;
		phil->in->fork[phil->id + 1] = 0;
		phil->se = 1;
	}
	return (0);
}

int		ft_sleep(t_sphilo *phil)//funcion de dormir
{
	if (phil->se == 1)
	{
		ft_printf (3, phil);
//		usleep (phil->in->ts* 1e3);
		ft_usleep (phil->in->ts, phil->in->tstart, phil->in->sd);
		phil->ss = 1;
		phil->se = 0;
	}
	return (0);
}

int		ft_think(t_sphilo *phil)//funcion de pensar
{
	if (phil->ss == 1)
	{
		ft_printf (4, phil);
//		ft_usleep (phil->in->tthink, phil->in->tstart);//a veces genera un delay de 10ms
		phil->ss = 0;
		--phil->in->ne[phil->id];
	}
	return (0);
}

int		ft_check(t_sphilo *phil)
{
	if (phil->sp == 0 && (phil->in->td < phil->lte))//condicion de no comer antes de morir
	{
//		pthread_mutex_lock (&phil->in->died);
		--phil->in->sd;
		ft_printf (5, phil);
		return (1);
	}
	if (phil->sp == 1 && (phil->in->td < (phil->lte - phil->lts)))//condicion de no haber comido después de la última vez
	{
//		pthread_mutex_lock (&phil->in->died);
		--phil->in->sd;
		ft_printf (5, phil);
		return (1);
	}
	phil->sp = 1;
	return (0);
}

long	ft_time(long tstart)
{
	struct timeval	s;
	long			res;
	
	gettimeofday(&s, NULL);
	res = ((s.tv_sec * 1e3) + (1e-3 * s.tv_usec)) - tstart;
//	printf ("res %ld\n", res);
	return (res);
}

void	ft_usleep(long time, long tstart, int sd)
{
	long	start;//tiempo inicial
	long	moment;//tiempo instantaneo

	start = ft_time(tstart);
	moment = ft_time(tstart);
	while (time >= (moment - start) && sd == 2)
	{	
		usleep (1000);
		moment = ft_time(tstart);
	}
}

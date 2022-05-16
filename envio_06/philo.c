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
	in.tthink = 0;  
	in.tstart = 0;
	in.tstart = ft_time(in.tstart);
	in.spf = 0;
	in.fork = (int *) malloc (sizeof(int) * (in.nph + 1));//malloc con +1 para el tenedor del ultimo filosofo
	in.mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * in.nph);
	if (in.fork == NULL || in.mutex == NULL || ft_start (&in) == 1)
	{
		ft_free_in(& in);
//		system ("leaks philo");
		return (1);
	}
	ft_free_in (&in);
//	system ("leaks philo");
	return(0);
}

int	ft_start (t_dat *in)//funcion que crea y destruye los hilos
{
	pthread_t		*t;
	t_sphilo		**phil;

	in->i = -1;
	phil = NULL;
	t = (pthread_t *) malloc(sizeof(pthread_t) * in->nph);
	phil = (t_sphilo **) malloc (sizeof(t_sphilo *) * in->nph);//proteger malloc
	while (++in->i < in->nph)
		phil[in->i] = ft_data (in->i, in);
	in->i = -1;
	pthread_mutex_init (&in->mspf, NULL);//inicio mutex de impresion
	while (++in->i < in->nph)
	{
		pthread_mutex_init (&phil[in->i]->in->mutex[in->i], NULL);//inicio los mutex
		if (pthread_create (&t[in->i], NULL, &ft_create, phil[in->i]) != 0)//creo los hilos
		{
			write (1,"Create pthread error\n", 21);
			return (1);//HAY QUE LIBERAR**
		}
	}
	in->j = -1;
	while (++in->j < in->nph)
	{
		pthread_join (t[in->j], NULL);
		pthread_mutex_destroy (&phil[in->j]->in->mutex[in->j]);
	}
	pthread_mutex_destroy (&in->mspf);
	ft_free_phil (phil, t);
	return (0);
}

t_sphilo	*ft_data(int i, t_dat *in)//carga datos iniciales a las variables de la estructura del filo
{
	t_sphilo	*phil;

//	phil = NULL;
	phil = (t_sphilo *) malloc (sizeof(t_sphilo));
	phil->in = in;//cargo la estructura in dentro de la phil
	phil->id = i;//añado el id de todos los filosofos
	in->fork[i] = 0;//pongo a cero todos los tenedores
	if (i == 0 && in->nph > 1)//pongo a cero el tenedor para el utlimo filosofo
		in->fork[in->nph] = in->fork[i];//poner punteros en vez de valores
	phil->sp = 0;//estado de primera pasada
	phil->se = 0;//estado de comidas
	phil->sem = 0;//estado de si ha comido alguna vez o no
	phil->sw = 0;//estado de si esperado la primera vez o no
	phil->ss = 0;//estado de dormidas
	phil->in->sd = 2;//estado de muerte (pongo 2 y hago -- en cuanto muere para que imprima solo 1 died)
	return (phil);
}

void	*ft_create(void *phil_anterior)//funcion que retiene los hilos
{
	t_sphilo		*phil;

	phil = (t_sphilo *) phil_anterior;
	while (phil->in->sd == 2)//bucle para retener los hilos 
	{
		if (phil->id % 2 == 0)//empiezan comiendo los impares (id+1 por el filosofo 0)
		{
			if (phil->sw == 1)
				usleep (50);//pequeño retardo a partir de la segunda vuelta para los filosofos impares y no se aturullen
			if (ft_take (phil) == 1)
				return ((void *)1);
			phil->sw = 1;
		}
		else
		{
			if (phil->sw == 0)
			{
				phil->sw = 1;
				if (ft_usleep ((phil->in->te), phil) == 1)
					return ((void *)1);
			}
			else
				usleep (50);//pequeño retardo para los filosofos pares y no se atropellen entre todos
			if (ft_take (phil) == 1)
				return ((void *)1);
		}
		if (phil->in->ne[phil->id] == 0 || ft_check_moment(phil))
			break;
	}
	return (0);
}

int		ft_take(t_sphilo *phil)//funcion para coger los tenedores
{
	if (phil->in->nph == 1)//caso de un filosofo
	{
		ft_printf (1, phil);
		while (ft_check (phil) != 1)
			phil->lte = ft_time(phil->in->tstart);
		phil->in->sd = 1;
		return (1);
	}
	if (phil->id != phil->in->nph - 1)
	{
		while (phil->in->fork[phil->id] == 0 && phil->in->fork[phil->id + 1] == 0 && phil->in->ne[phil->id] != 0 && phil->se == 0 && phil->in->sd == 2 && phil->in->nph > 1)
		{
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
	}
	else
	{
		while (phil->in->fork[phil->id] == 0 && phil->in->fork[0] == 0 && phil->in->ne[phil->id] != 0 && phil->se == 0 && phil->in->sd == 2 && phil->in->nph > 1)
		{
			{
				pthread_mutex_lock (&phil->in->mutex[phil->id]);
				pthread_mutex_lock (&phil->in->mutex[0]);
				phil->in->fork[phil->id] = 1;
				phil->in->fork[0] = 1;
				ft_printf (1, phil);
				ft_printf (1, phil);
			}
			if (ft_eat_last(phil) == 1)
				return (1);
		}
	}
	if (phil->in->sd == 2)
		if (ft_sleep(phil) == 1)
			return (1);
	if (phil->in->sd == 2)
		if (ft_think(phil) == 1)
			return (1);
	return (0);
}

int		ft_eat(t_sphilo *phil)//funcion de comer
{
	if (phil->in->fork[phil->id] == 1 && phil->in->fork[phil->id + 1] == 1)
	{
		if (phil->sp == 1)
			phil->lts = phil->lte;
		else
			phil->lts = ft_time(phil->in->tstart);
//		printf ("id(%d) - lts: %ld\n", phil->id + 1, phil->lts);
		phil->lte = ft_time(phil->in->tstart);
		if (ft_check (phil) == 1)
		{
//			printf ("Comiendo\n");
			return (1);
		}
		ft_printf (2, phil); 
//		ft_usleep (phil->in->te, phil->in->tstart, phil->in->sd);
		phil->sem = 1;
		if (ft_usleep (phil->in->te, phil) == 1)
			return (1);
		pthread_mutex_unlock (&phil->in->mutex[phil->id]);
		pthread_mutex_unlock (&phil->in->mutex[phil->id + 1]);
		phil->in->fork[phil->id] = 0;
		phil->in->fork[phil->id + 1] = 0;
		phil->se = 1;
	}
	return (0);
}

int		ft_eat_last(t_sphilo *phil)//funcion de comer el ultimo philosofo
{
	if (phil->in->fork[phil->id] == 1 && phil->in->fork[0] == 1)
	{
		if (phil->sp == 1)
			phil->lts = phil->lte;
		else
			phil->lts = ft_time(phil->in->tstart);
//		printf ("id(%d) - lts: %ld\n", phil->id + 1, phil->lts);
		phil->lte = ft_time(phil->in->tstart);
		if (ft_check (phil) == 1)
		{
//			printf ("Comiendo\n");
			return (1);
		}
		ft_printf (2, phil); 
//		ft_usleep (phil->in->te, phil->in->tstart, phil->in->sd);
		phil->sem = 1;
		if (ft_usleep (phil->in->te, phil) == 1)
			return (1);
		pthread_mutex_unlock (&phil->in->mutex[phil->id]);
		pthread_mutex_unlock (&phil->in->mutex[0]);
		phil->in->fork[phil->id] = 0;
		phil->in->fork[0] = 0;
		phil->se = 1;
	}
	return (0);
}

int		ft_sleep(t_sphilo *phil)//funcion de dormir
{
	if (ft_check (phil) == 1)
	{
//		printf ("Durmiendo\n");
		return (1);
	}
	if (phil->se == 1)
	{
		ft_printf (3, phil);
		if (ft_usleep (phil->in->ts, phil) == 1)
			return (1);
		phil->ss = 1;
	}
	return (0);
}

int		ft_think(t_sphilo *phil)//funcion de pensar
{
	if (ft_check (phil) == 1)
	{
//		printf ("Pensando\n");
		return (1);
	}
	if (phil->ss == 1)
	{
		ft_printf (4, phil);
//		if (phil->in->nph % 2 != 0)
		{
			if (ft_usleep (1 * phil->in->nph, phil) == 1)//tthink es 0, se podria quitar
				return (1);
		}
		phil->se = 0;
		phil->ss = 0;
		phil->sp = 1;
		--phil->in->ne[phil->id];
	}
	return (0);
}

//chequea la muerte al inicio de cada funcion
int		ft_check(t_sphilo *phil)
{
	if (phil->sp == 0 && (phil->in->td < phil->lte))//condicion de no comer antes de morir
	{
		--phil->in->sd;
//		printf ("HOLA\n");
		ft_printf (5, phil);
		return (1);
	}
	if (phil->sp == 1 && (phil->in->td < (phil->lte - phil->lts)))//condicion de no haber comido después de la última vez
	{
//		printf ("ADIOS\n");
//		printf ("phil->sp de id(%d): %d\n", phil->id + 1, phil->sp);
//		printf ("id(%d) - td: %ld - lts: %ld\n", phil->id + 1, phil->in->td, phil->lts);
		--phil->in->sd;
		ft_printf (5, phil);
		return (1);
	}
	if (phil->se == 1 && phil->ss == 1)
		phil->sp = 1;
	return (0);
}

//chequea la muerte en el usleep propio
int		ft_check_moment(t_sphilo *phil)
{
	if (phil->sem == 0 && (phil->in->td < ft_time(phil->in->tstart)))//condicion de no comer antes de morir
	{
//		printf ("inicio\n");
		--phil->in->sd;
		ft_printf (5, phil);
		return (1);
	}
	if (phil->sem == 1 && (phil->in->td < (ft_time(phil->in->tstart) - phil->lte)))//condicion de no haber comido después de la última vez
	{
//		printf ("siguientes\n");
		--phil->in->sd;
		ft_printf (5, phil);
		return (1);
	}
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

int	ft_usleep(long time, t_sphilo *phil)
{
	long	start;//tiempo inicial
	long	moment;//tiempo instantaneo

	start = ft_time(phil->in->tstart);
	moment = ft_time(phil->in->tstart);
	while (time >= (moment - start) && phil->in->sd == 2)
	{	
		usleep (500);
		moment = ft_time(phil->in->tstart);
		if (ft_check_moment (phil) == 1)
			return(1);
	}
	return (0);
}

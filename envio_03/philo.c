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
		return (1);//hay que liberar
	if (ft_par_start (&in) == 1)
		return (1);//hay que liberar!!!
	free (in.fork);
	return(0);
}

int	ft_par_start (t_dat *in)
{
	pthread_t		t[in->nph];
	t_sphilo		*phil;

	in->i = -1;
	while (++in->i < in->nph)
	{
		phil = NULL;
		phil = (t_sphilo *) malloc (sizeof(t_sphilo));//proteger malloc
		phil->in = in;
		phil->id = in->i;//añado el id de todos los filosofos
		in->fork[in->i] = 0;//pongo a cero todos los tenedores
		if (in->i == 0)//pongo a cero el tenedor para el utlimo filosofo
			in->fork[in->nph] = in->fork[in->i];
		phil->sp = 0;//estado de primera pasada
		phil->se = 0;//estado de comidas
		phil->ss = 0;//estado de dormidas
		phil->in->tfinal = 0;//buleano de muerte
		pthread_mutex_init (&phil->in->mutex[in->i], NULL);
		if (pthread_create (&t[in->i], NULL, &ft_create, phil) != 0)
		{
			write (1,"Create pthread error\n", 21);
//			ft_free (in);
			return (1);
		}
		if (phil->in->tfinal == 1)
			return (1);
	}
	in->j = -1;
	while (++in->j < in->nph)// && phil->sp != 0)
	{
		pthread_join (t[in->j], (void **) &phil);
		free (phil);
//		pthread_mutex_destroy (&phil->in->mutex[in->j]);//me da SEGF
//		free (&phil->in->mutex[in->j]);
	}
	return (0);
}

void	*ft_create(t_sphilo *phil)
{
	while (1)//bucle infinito para retener los hilos 
	{
		if (phil->id % 2 == 0)//empiezan comiendo los impares (id+1 por el filosofo 0)
		{
			if (ft_take (phil) == 1)
				return ((void *)1);
		}
		else//if (phil->id % 2 != 0)
		{
			usleep (50);
			if (ft_take (phil) == 1)
				return ((void *)1);
		}
//		if (phil->in->ne[phil->id] == 0)
//			break;
	}
	return (0);
}

int		ft_take(t_sphilo *phil)
{
	while (phil->in->fork[phil->id] == 0 && phil->in->fork[phil->id + 1] == 0 && phil->in->ne[phil->id] != 0 && phil->se == 0 && phil->in->tfinal == 0)
	{
		if (phil->in->fork[phil->id] == 0 && phil->in->fork[(phil->id) + 1] == 0 && phil->in->tfinal == 0)
		{
			pthread_mutex_lock (&phil->in->mutex[phil->id]);
			pthread_mutex_lock (&phil->in->mutex[phil->id + 1]);
			phil->in->fork[phil->id] = 1;
			phil->in->fork[(phil->id) + 1] = 1;
			printf ("%6.3f %d has taken a fork\n", ft_time(phil->in->tstart), phil->id);
		}
		ft_eat(phil);
	}
	ft_sleep(phil);
	ft_think(phil);
//	if (phil->in->ne[phil->id] > 0 && phil->in->tfinal == 0)
//		--phil->in->ne[phil->id];
	return (0);
}

int		ft_eat(t_sphilo *phil)
{
	if (phil->in->fork[phil->id] == 1 && phil->in->fork[phil->id + 1] == 1 && phil->in->tfinal == 0)
	{
		phil->lts = phil->lte;
		phil->lte = ft_time(phil->in->tstart);
		if (ft_check (phil) == 1)
			return (1);
		printf ("%6.3f %d is eating\n", phil->lte, phil->id); 
		ft_usleep (phil->in->te, phil->in->tstart);
		pthread_mutex_unlock (&phil->in->mutex[phil->id]);
		pthread_mutex_unlock (&phil->in->mutex[phil->id + 1]);
		phil->in->fork[phil->id] = 0;
		phil->in->fork[phil->id + 1] = 0;
		phil->se = 1;
	}
	return (0);
}

int		ft_sleep(t_sphilo *phil)
{
	if (phil->se == 1 && phil->in->tfinal == 0)
	{
		printf ("%6.3f %d is sleeping\n", ft_time(phil->in->tstart), phil->id); 
		ft_usleep (phil->in->ts, phil->in->tstart);
		phil->ss = 1;
		phil->se = 0;
	}
	return (0);
}

int		ft_think(t_sphilo *phil)
{
	if (phil->ss == 1 && phil->in->tfinal == 0)
	{
		printf ("%6.3f %d is thinking\n", ft_time(phil->in->tstart), phil->id); 
//		ft_usleep (phil->in->tthink, phil->in->tstart);
		phil->ss = 0;
	}
	return (0);
}

void	ft_usleep(double time, double tstart)
{
	double	start;//tiempo inicial
	double	moment;//tiempo instantaneo

	start = ft_time(tstart);
	moment = ft_time(tstart);
	while (time > (moment - start))
	{	
		usleep (50);
		moment = ft_time(tstart);
	}
}

int		ft_check(t_sphilo *phil)
{
	if (phil->sp == 0 && (phil->in->td < phil->lte))//condicion de no comer antes de morir
	{
		phil->in->tfinal = 1;
		printf ("El filosofo %d con %f de comida muere - 1\n", phil->id + 1, phil->lte);
		return (1);
	}
//	if (phil->sp == 1)
//	printf ("Tiempo calculado es: %f\n", (phil->lte - phil->lts) * 1e3);
	if (phil->sp == 1 && (phil->in->td * 1e3 < round ((phil->lte - phil->lts)* 1e3)))//condicion de no haber comido después de la última vez
	{
		phil->in->tfinal = 1;
		printf ("El filosofo %d con %f de comida muere - 2\n", phil->id + 1, (phil->lte - phil->lts));
		return (1);
	}
	phil->sp = 1;
	return (0);
}

double	ft_time(double tstart)
{
	struct timeval	s;
	double			res;
	
	gettimeofday(&s, NULL);
	res = (s.tv_sec + (1e-6 * s.tv_usec)) - tstart;//compongo el tiempo con parte entera y decimal
//	printf ("res %f\n", res);
	return (res);
}

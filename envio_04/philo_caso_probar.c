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
	in.nfk = (int *) malloc (sizeof(int) * (in.nph));
	if (in.nfk == NULL)
		return (0);
	in.tstart = 0;
	in.tstart = ft_time(in.tstart);
	if (in.ne == 0)//si no hay numero de comidas	
	{	
		while (1)
		{
			if (ft_par_start (&in) == 1)
				return (1);//hay que liberar!!!
		}
	}
	else//si hay numero de comidas minimo
	{
		while (--in.ne >= 0)
		{
			if (ft_par_start (&in) == 1)
				return (1);//hay que liberar!!!
		}
	}
//	ft_free (&in);	
	return(0);
}

int	ft_par_start (t_dat *in)
{
	pthread_t	t[in->nph];
	t_sphilo	*phil;

	in->i = -1;
	while (++in->i <= in->nph)
	{
		phil = malloc (sizeof(t_sphilo));
//		phil->in->nfk[in->i] = in->nfk[in->i];
//		phil->in->nfk = (int *) malloc (sizeof(int) * (in->nph));
		phil->id = in->i;
		in->nfk[in->i] = 0;

		if (pthread_create (&t[in->i], NULL, &ft_create, phil) != 0)
		{
			write (1,"Create pthread error\n", 21);
//			ft_free (in);
			return (1);
		}
	}
	in->j = -1;
	while (++in->j < in->nph)
	{
		pthread_join (t[in->j], (void **) &phil);
//		printf ("Despues del bucle: %f\n", phil->lte);
		free (phil);
	}
	return (0);
}

void	*ft_create(t_sphilo *phil)
{
	phil->lte = ft_time(phil->in->tstart);
	printf ("El id: %d\n", phil->id);
	if (phil->in->nfk[phil->id] == 0)	
	{
		phil->in->nfk[phil->id] = 1;
		printf ("%5.3f %d has taken a fork\n", phil->lte, phil->id);
	}
	return ((void *) phil);
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

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
	in.lte = (double *) malloc (sizeof (double) * (in.nph));
	in.lts = (double *) malloc (sizeof (double) * (in.nph));
	if (in.ne == 0)//si no hay numero de comidas	
	{	
		in.ltstart = ft_time();
		while (1)
		{
			if (ft_start (&in) == 1)
				return (1);
		}
	}
	else//si hay numero de comidas minimo
	{
		in.ltstart = ft_time();
		printf ("TIME START: %14.3f\n", in.ltstart);
		printf ("TIME DIE: %14.3f\n", in.td);
		printf ("TIME START + TIME DIE: %14.3f\n", in.ltstart + in.td);
		while (--in.ne >= 0)
		{
			if (ft_start (&in) == 1)
				return (1);
		}
	}
	ft_free (&in);	
	return(0);
}

int	ft_start (t_dat *in)
{
	pthread_t	pth[in->nph];
	t_dat		*a;
	
	in->i = -1;
	while (++in->i < in->nph)
	{
		in->lte[in->i] = ft_time();
		printf ("%14.3f %d has taken a fork\n", in->lte[in->i], in->i);
		if ((in->lte[in->i] < (in->ltstart + in->td)) || (in->lte[in->i] < (in->lts[in->i] + in->td)))
		{
			a = malloc (sizeof (t_dat));
			*a = *in;	
			if (pthread_create (&pth[in->i], NULL, &ft_eat, a) != 0)
			{
				perror ("Create pthread error");
				ft_free (in);
				return (1);
			}
		}
		else
		{
			in->ltfinal = ft_time();
			printf ("%14.3f %d died\n", in->ltfinal, in->i);
			ft_free (in);
			return(1);
		}

	}
	in->j = -1;
	while (++in->j < in->nph)
		pthread_join (pth[in->j], NULL);
	return (0);
}

void	*ft_eat(void *a)
{
	t_dat new = *(t_dat *) a;
	
	printf ("%14.3f %d is eating\n", ft_time(), new.i);
	usleep (new.te * 1e6);
	new.lts[new.i] = ft_time();
	printf ("%14.3f %d is sleeping\n", new.lts[new.i], new.i);
	usleep (new.ts * 1e6);
	printf ("%14.3f %d is thinking\n", ft_time(), new.i);
	free (a);
	return (0);
}

double	ft_time()
{
	struct timeval	s;
	double			res;
	
	gettimeofday(&s, NULL);
	res = s.tv_sec + (1e-6 * s.tv_usec);//compongo el tiempo con parte entera y decimal
//	printf ("res %f\n", res);
	return (res);
}

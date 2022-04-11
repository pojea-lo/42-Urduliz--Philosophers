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
	if (in.ne == 0)//si no hay numero de comidas	
	{
		while (1)
		{
			if (ft_start (&in) == 1)
				return (1);
		}
	}
	else//si hay numero de comidas minimo
	{
		while (--in.ne >= 0)
		{
			if (ft_start (&in) == 1)
				return (1);
		}
	}	
	return(0);
}

int	ft_start (t_dat *in)
{
	pthread_t	pth[in->nph];
	t_dat		*a;
	in->lte = (float *) malloc (sizeof (float) * (in->nph));
	in->lts = (float *) malloc (sizeof (float) * (in->nph));
	
	in->i = -1;
//	in->ltstart = ft_time();
	while (++in->i < in->nph)
	{
	//	in->lte[in->i] = ft_time();
	//	printf ("%f %d has taken a fork\n", in->lte[in->i], in->i);
	//	if (())
		a = malloc (sizeof (t_dat));
		*a = *in;	
		if (pthread_create (&pth[in->i], NULL, &ft_eat, a) != 0)
		{
			perror ("Create pthread error");
			return (1);
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
	
	printf ("%f %d is eating\n", ft_time(), new.i);
	usleep (new.te * 1000);
//	new.lts[new.i] = ft_time();
//	printf ("%f %d is sleeping\n", new.lts[new.i], new.i);
	usleep (new.ts * 1000);
//	printf ("%f %d is thinking\n", ft_time(), new.i);
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

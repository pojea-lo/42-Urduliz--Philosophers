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
	if (ft_start (&in) == 1)
		return (1);
	return(0);
}

int	ft_start (t_dat *in)
{
	int			i;
	pthread_t	pth[in->nph];

	i = -1;
	while (++i < in->nph)
	{
		if (pthread_create (&pth[i], NULL, &ft_eat, NULL) != 0)
		{
			perror ("Create pthread error");
			return (1);
		}
	}
	i = -1;
	while (++i < in->nph)
		pthread_join (pth[i], NULL);
	return (0);
}

void	*ft_eat()
{
	ft_time();
	return (0);
}

long int	ft_time()
{
	struct timeval	t;
	
	gettimeofday(&t, NULL);
	printf ("En segundos time:      %ld\n", (long int) t.tv_sec);
	printf ("En microsegundos time: %ld\n", (long int) t.tv_usec);
	return (0);
}

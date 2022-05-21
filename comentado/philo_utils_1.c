#include "philo.h"

void	ft_printf(int i, t_sphilo *phil)
{
	pthread_mutex_lock (&phil->in->mspf);
	if (i == 1 && phil->in->sd == 2 && phil->in->spf == 0)
	{
		printf ("%.5ld %d has taken a fork\n", ft_time(phil->in->tstart), phil->id + 1);
	}
	if (i == 2 && phil->in->sd == 2 && phil->in->spf == 0)
	{
		printf ("%.5ld %d is eating\n", phil->lte, phil->id + 1);
	}
	if (i == 3 && phil->in->sd == 2 && phil->in->spf == 0)
	{
		printf ("%.5ld %d is sleeping\n", ft_time(phil->in->tstart), phil->id + 1);
	}
	if (i == 4 && phil->in->sd == 2 && phil->in->spf == 0)
	{
		printf ("%.5ld %d is thinking\n", ft_time(phil->in->tstart), phil->id + 1);
	}
	if (i == 5 && phil->in->sd == 1 && phil->in->spf == 0)
	{
		phil->in->spf = 1;
		printf ("\033[31m%.5ld %d is dead\n\E[37m", ft_time(phil->in->tstart), phil->id + 1);
//		usleep (5000);
	}
	pthread_mutex_unlock (&phil->in->mspf);
}

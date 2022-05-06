#include "philo.h"

void	ft_printf(int i, t_sphilo *phil)
{
	if (i == 1 && phil->in->sd == 2)// && phil->id == 199)
	{
		printf ("%.5ld %d has taken a fork\n", ft_time(phil->in->tstart), phil->id + 1);
	}
	if (i == 2 && phil->in->sd == 2)
	{
		printf ("%.5ld %d is eating\n", phil->lte, phil->id + 1);
	}
	if (i == 3 && phil->in->sd == 2)
	{
		printf ("%.5ld %d is sleeping\n", ft_time(phil->in->tstart), phil->id + 1);
	}
	if (i == 4 && phil->in->sd == 2)
	{
		printf ("%.5ld %d is thinking\n", ft_time(phil->in->tstart), phil->id + 1);
	}
	if (i == 5 && phil->in->sd == 1)//de vez en cuando falla la impresion
	{
		usleep (500);
		printf ("\033[31m%.5ld %d is dead\n\E[37m", ft_time(phil->in->tstart), phil->id + 1);
	}
}

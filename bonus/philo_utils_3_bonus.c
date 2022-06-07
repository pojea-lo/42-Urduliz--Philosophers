#include "philo_bonus.h"

int	ft_create(t_dat *in)
{
	while (in->sd == 2)
	{
		if (ft_take(in) == 1)
			return (1);
		if (in->ne == 0)
			return (1);
	}
	return (0);
}

int	ft_take(t_dat *in)
{
	if (in->nph == 1)
	{
		ft_printf (1, in);
		in->lte = ft_time(in->tstart);
		while (ft_check (in) != 1)
			in->lte = ft_time(in->tstart);
		in->sd = 1;
		return (1);
	}
	if (ft_take_rest(in) == 1)
		return (1);
	if (in->sd == 2 && in->se == 1)
	{
		if (ft_sleep(in) == 1)
			return (1);
	}
	if (in->sd == 2 && in->se == 1 && in->ss == 1)
	{
		if (ft_think(in) == 1)
			return (1);
	}
	return (0);
}

int	ft_take_rest(t_dat *in)
{
	int	tt;//tiempo de espera

	tt = in->te - in->ts;
	while (in->ne != 0 && in->se == 0 && in->sd == 2)
	{
		if (in->id < in->nph / 2 && in->sem == 1 && tt > 0)
		{
			if (ft_usleep (tt, in) == 1)
				return (1);
		}
		sem_wait (in->semfork);
		sem_wait (in->semfork);
		ft_printf (1, in);
		ft_printf (1, in);
		if (ft_eat(in) == 1)
			return (1);
	}
	return (0);
}

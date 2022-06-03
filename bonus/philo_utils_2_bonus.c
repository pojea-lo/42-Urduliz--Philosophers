#include "philo_bonus.h"

int	ft_eat(t_dat *in)
{
	if (in->sp == 1)
		in->lts = in->lte;
	else
		in->lts = ft_time(in->tstart);
	in->lte = ft_time(in->tstart);
	if (ft_check (in) == 1)
		return (1);
	ft_printf (2, in);
	in->sem = 1;
	if (ft_usleep (in->te, in) == 1)
		return (1);
	sem_post (in->semfork);
	sem_post (in->semfork);
	in->se = 1;
	return (0);
}

int	ft_sleep(t_dat *in)
{
	if (ft_check (in) == 1)
		return (1);
	if (in->se == 1)
	{
		ft_printf (3, in);
		if (ft_usleep (in->ts, in) == 1)
			return (1);
		in->ss = 1;
	}
	return (0);
}

int	ft_think(t_dat *in)
{
	if (ft_check (in) == 1)
		return (1);
	if (in->ss == 1)
	{
		ft_printf (4, in);
		if (in->id <= 100 && (in->nph % 2 != 0))
			usleep (in->nph * 100);
		if (in->id > 100 && (in->nph % 2 != 0))
			usleep (in->nph * 50);
		in->se = 0;
		in->ss = 0;
		in->sp = 1;
		--in->ne;
	}
	return (0);
}

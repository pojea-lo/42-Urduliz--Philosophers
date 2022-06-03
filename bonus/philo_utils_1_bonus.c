#include "philo_bonus.h"

int	ft_printf(int i, t_dat *in)
{
	sem_wait(in->mspf);
	if (i == 1 && in->sd == 2 && in->spf == 0)
		printf ("%.5ld %d has taken a fork\n", ft_time(in->tstart),
			in->id + 1);
	if (i == 2 && in->sd == 2 && in->spf == 0)
		printf ("%.5ld %d is eating\n", in->lte, in->id + 1);
	if (i == 3 && in->sd == 2 && in->spf == 0)
		printf ("%.5ld %d is sleeping\n", ft_time(in->tstart),
			in->id + 1);
	if (i == 4 && in->sd == 2 && in->spf == 0)
		printf ("%.5ld %d is thinking\n", ft_time(in->tstart), in->id
			+ 1);
	if (i == 5 && in->sd == 1 && in->spf == 0)
	{
		in->spf = 1;
		printf ("\033[31m%.5ld %d is dead\n\E[37m", ft_time(in->tstart),
			in->id + 1);
		return (1);
	}
	sem_post(in->mspf);
	return (0);
}

int	ft_check(t_dat *in)
{
	if (in->sp == 0 && (in->td < in->lte) && in->sd == 2)
	{
		--in->sd;
		ft_printf (5, in);
		return (1);
	}
	if (in->sp == 1 && (in->td < (in->lte - in->lts)) && in->sd == 2)
	{
		--in->sd;
		ft_printf (5, in);
		return (1);
	}
	if (in->se == 1 && in->ss == 1)
		in->sp = 1;
	return (0);
}

int	ft_check_moment(t_dat *in)
{
	if (in->sem == 0 && (in->td < ft_time(in->tstart)) && in->sd == 2)
	{
		--in->sd;
		ft_printf (5, in);
		return (1);
	}
	if (in->sem == 1 && (in->td < (ft_time(in->tstart) - in->lte)) && in->sd == 2)
	{
		--in->sd;
		ft_printf (5, in);
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
	return (res);
}

int	ft_usleep(long time, t_dat *in)
{
	long	start;
	long	moment;

	start = ft_time(in->tstart);
	moment = ft_time(in->tstart);
	while (time >= (moment - start) && in->sd == 2)
	{
		usleep (500);
		moment = ft_time(in->tstart);
		if (ft_check_moment (in) == 1)
			return (1);
	}
	return (0);
}

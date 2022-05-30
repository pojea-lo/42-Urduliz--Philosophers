/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:14:01 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/05/30 18:36:32 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(int i, t_sphilo *phil)
{
	pthread_mutex_lock (&phil->in->mspf);
	if (i == 1 && phil->in->sd == 2 && phil->in->spf == 0)
		printf ("%.5ld %d has taken a fork\n", ft_time(phil->in->tstart),
			phil->id + 1);
	if (i == 2 && phil->in->sd == 2 && phil->in->spf == 0)
		printf ("%.5ld %d is eating\n", phil->lte, phil->id + 1);
	if (i == 3 && phil->in->sd == 2 && phil->in->spf == 0)
		printf ("%.5ld %d is sleeping\n", ft_time(phil->in->tstart),
			phil->id + 1);
	if (i == 4 && phil->in->sd == 2 && phil->in->spf == 0)
		printf ("%.5ld %d is thinking\n", ft_time(phil->in->tstart), phil->id
			+ 1);
	if (i == 5 && phil->in->sd == 1 && phil->in->spf == 0)
	{
		phil->in->spf = 1;
		printf ("\033[31m%.5ld %d is dead\n\E[37m", ft_time(phil->in->tstart),
			phil->id + 1);
	}
	pthread_mutex_unlock (&phil->in->mspf);
}

int	ft_check(t_sphilo *phil)
{
	pthread_mutex_lock (&phil->in->dead);
	if (phil->sp == 0 && (phil->in->td < phil->lte))
	{
		--phil->in->sd;
		ft_printf (5, phil);
		pthread_mutex_unlock (&phil->in->dead);
		return (1);
	}
	if (phil->sp == 1 && (phil->in->td < (phil->lte - phil->lts)))
	{
		--phil->in->sd;
		ft_printf (5, phil);
		pthread_mutex_unlock (&phil->in->dead);
		return (1);
	}
	if (phil->se == 1 && phil->ss == 1)
		phil->sp = 1;
	pthread_mutex_unlock (&phil->in->dead);
	return (0);
}

int	ft_check_moment(t_sphilo *ph)
{
	pthread_mutex_lock (&ph->in->dead);
	if (ph->sem == 0 && (ph->in->td < ft_time(ph->in->tstart)))
	{
		--ph->in->sd;
		ft_printf (5, ph);
		pthread_mutex_unlock (&ph->in->dead);
		return (1);
	}
	if (ph->sem == 1 && (ph->in->td < (ft_time(ph->in->tstart) - ph->lte)))
	{
		--ph->in->sd;
		ft_printf (5, ph);
		pthread_mutex_unlock (&ph->in->dead);
		return (1);
	}
	pthread_mutex_unlock (&ph->in->dead);
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

int	ft_usleep(long time, t_sphilo *phil)
{
	long	start;
	long	moment;

	start = ft_time(phil->in->tstart);
	moment = ft_time(phil->in->tstart);
	while (time >= (moment - start) && phil->in->sd == 2)
	{
		usleep (500);
		moment = ft_time(phil->in->tstart);
		if (ft_check_moment (phil) == 1)
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:23:20 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/05/22 15:23:42 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_sphilo *phil)
{
	if (phil->in->fork[phil->id] == 1 && phil->in->fork[phil->id + 1] == 1)
	{
		if (phil->sp == 1)
			phil->lts = phil->lte;
		else
			phil->lts = ft_time(phil->in->tstart);
		phil->lte = ft_time(phil->in->tstart);
		if (ft_check (phil) == 1)
			return (1);
		ft_printf (2, phil);
		phil->sem = 1;
		if (ft_usleep (phil->in->te, phil) == 1)
			return (1);
		pthread_mutex_unlock (&phil->in->mutex[phil->id]);
		pthread_mutex_unlock (&phil->in->mutex[phil->id + 1]);
		phil->in->fork[phil->id] = 0;
		phil->in->fork[phil->id + 1] = 0;
		phil->se = 1;
	}
	return (0);
}

int	ft_eat_last(t_sphilo *phil)
{
	if (phil->in->fork[phil->id] == 1 && phil->in->fork[0] == 1)
	{
		if (phil->sp == 1)
			phil->lts = phil->lte;
		else
			phil->lts = ft_time(phil->in->tstart);
		phil->lte = ft_time(phil->in->tstart);
		if (ft_check (phil) == 1)
			return (1);
		ft_printf (2, phil);
		phil->sem = 1;
		if (ft_usleep (phil->in->te, phil) == 1)
			return (1);
		pthread_mutex_unlock (&phil->in->mutex[phil->id]);
		pthread_mutex_unlock (&phil->in->mutex[0]);
		phil->in->fork[phil->id] = 0;
		phil->in->fork[0] = 0;
		phil->se = 1;
	}
	return (0);
}

int	ft_sleep(t_sphilo *phil)
{
	if (ft_check (phil) == 1)
		return (1);
	if (phil->se == 1)
	{
		ft_printf (3, phil);
		if (ft_usleep (phil->in->ts, phil) == 1)
			return (1);
		phil->ss = 1;
	}
	return (0);
}

int	ft_think(t_sphilo *phil)
{
	if (ft_check (phil) == 1)
		return (1);
	if (phil->ss == 1)
	{
		ft_printf (4, phil);
		if (phil->id <= 100 && (phil->in->nph % 2 != 0))
			usleep (phil->in->nph * 100);
		if (phil->id > 100 && (phil->in->nph % 2 != 0))
			usleep (phil->in->nph * 50);
		phil->se = 0;
		phil->ss = 0;
		phil->sp = 1;
		--phil->in->ne[phil->id];
	}
	return (0);
}

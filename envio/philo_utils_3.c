/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:28:02 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/05/22 15:51:35 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *phil_anterior)
{
	t_sphilo		*phil;

	phil = (t_sphilo *) phil_anterior;
	while (phil->in->sd == 2)
	{
		if (phil->id % 2 == 0)
		{
			if (phil->sw == 1)
				usleep (50);
			if (ft_take (phil) == 1)
				return ((void *)1);
			phil->sw = 1;
		}
		else
		{
			if (ft_create_aux (phil) == 1)
				return ((void *)1);
		}
		if (phil->in->ne[phil->id] == 0 || ft_check_moment(phil))
			break ;
	}
	return (0);
}

int	ft_create_aux(t_sphilo *phil)
{
	if (phil->sw == 0)
	{
		phil->sw = 1;
		if (ft_usleep ((phil->in->te), phil) == 1)
			return (1);
	}
	else
		usleep (50);
	if (ft_take (phil) == 1)
		return (1);
	return (0);
}

int	ft_take(t_sphilo *phil)
{
	if (phil->in->nph == 1)
	{
		ft_printf (1, phil);
		while (ft_check (phil) != 1)
			phil->lte = ft_time(phil->in->tstart);
		phil->in->sd = 1;
		return (1);
	}
	if (ft_take_rest(phil) == 1)
		return (1);
	if (ft_take_last(phil) == 1)
		return (1);
	if (phil->in->sd == 2 && phil->se == 1)
	{
		if (ft_sleep(phil) == 1)
			return (1);
	}
	if (phil->in->sd == 2 && phil->se == 1 && phil->ss == 1)
	{
		if (ft_think(phil) == 1)
			return (1);
	}
	return (0);
}

int	ft_take_rest(t_sphilo *phil)
{
	if (phil->id != phil->in->nph - 1)
	{
		while (phil->in->fork[phil->id] == 0 && phil->in->fork[phil->id + 1]
			== 0 && phil->in->ne[phil->id] != 0 && phil->se == 0
			&& phil->in->sd == 2 && phil->in->nph > 1)
		{
			pthread_mutex_lock (&phil->in->mutex[phil->id]);
			pthread_mutex_lock (&phil->in->mutex[phil->id + 1]);
			phil->in->fork[phil->id] = 1;
			phil->in->fork[(phil->id) + 1] = 1;
			ft_printf (1, phil);
			ft_printf (1, phil);
			if (ft_eat(phil) == 1)
				return (1);
		}
	}
	return (0);
}

int	ft_take_last(t_sphilo *phil)
{
	if (phil->id == phil->in->nph - 1)
	{
		while (phil->in->fork[phil->id] == 0 && phil->in->fork[0] == 0
			&& phil->in->ne[phil->id] != 0 && phil->se == 0 && phil->in->sd
			== 2 && phil->in->nph > 1)
		{
			pthread_mutex_lock (&phil->in->mutex[phil->id]);
			pthread_mutex_lock (&phil->in->mutex[0]);
			phil->in->fork[phil->id] = 1;
			phil->in->fork[0] = 1;
			ft_printf (1, phil);
			ft_printf (1, phil);
			if (ft_eat_last(phil) == 1)
				return (1);
		}
	}
	return (0);
}

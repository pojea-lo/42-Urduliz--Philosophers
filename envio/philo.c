/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:46:00 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/05/22 15:10:45 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	in.tthink = 0;
	in.tstart = 0;
	in.tstart = ft_time(in.tstart);
	in.spf = 0;
	in.fork = (int *) malloc (sizeof(int) * (in.nph + 1));
	in.mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * in.nph);
	if (in.fork == NULL || in.mutex == NULL || ft_start (&in) == 1)
	{
		ft_free_in(& in);
		return (1);
	}
	ft_free_in (&in);
	return (0);
}

int	ft_start(t_dat *in)
{
	pthread_t		*t;
	t_sphilo		**phil;

	in->i = -1;
	phil = NULL;
	t = (pthread_t *) malloc(sizeof(pthread_t) * in->nph);
	phil = (t_sphilo **) malloc (sizeof(t_sphilo *) * in->nph);
	if (t == NULL || phil == NULL)
	{
		ft_free_phil (phil, t);
		return (1);
	}
	while (++in->i < in->nph)
		phil[in->i] = ft_data (in->i, in);
	if (ft_start_two (t, phil) == 1)
	{
		ft_free_phil (phil, t);
		return (1);
	}
	ft_free_phil (phil, t);
	return (0);
}

int	ft_start_two(pthread_t *t, t_sphilo **phil)
{
	int	i;
	int	j;

	i = -1;
	pthread_mutex_init (&phil[0]->in->mspf, NULL);
	while (++i < phil[0]->in->nph)
	{
		pthread_mutex_init (&phil[i]->in->mutex[i], NULL);
		if (pthread_create (&t[i], NULL, &ft_create, phil[i]) != 0)
		{
			write (1, "Create pthread error\n", 21);
			ft_free_phil (phil, t);
			return (1);
		}
	}
	j = -1;
	while (++j < phil[0]->in->nph)
	{
		pthread_join (t[j], NULL);
		pthread_mutex_destroy (&phil[j]->in->mutex[j]);
	}
	pthread_mutex_destroy (&phil[0]->in->mspf);
	return (0);
}

t_sphilo	*ft_data(int i, t_dat *in)
{
	t_sphilo	*phil;

	phil = (t_sphilo *) malloc (sizeof(t_sphilo));
	phil->in = in;
	phil->id = i;
	in->fork[i] = 0;
	if (i == 0 && in->nph > 1)
		in->fork[in->nph] = in->fork[i];
	phil->sp = 0;
	phil->se = 0;
	phil->sem = 0;
	phil->sw = 0;
	phil->ss = 0;
	phil->in->impi = 0;
	phil->in->impp = 0;
	phil->in->sd = 2;
	return (phil);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:11:47 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/05/22 15:13:11 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_argm_input(int argc, char *argv[], t_dat *in)
{
	int	i;

	in->nph = ft_atoi (argv[1]);
	in->td = ft_atoi (argv[2]);
	in->te = ft_atoi (argv[3]);
	in->ts = ft_atoi (argv[4]);
	in->ne = (int *) malloc (sizeof(int) * in->nph);
	if (argc == 5)
	{
		i = -1;
		while (++i < in->nph)
			in->ne[i] = -3;
	}
	else
	{
		i = -1;
		while (++i < in->nph)
			in->ne[i] = ft_atoi (argv[5]);
	}
	if (ft_argm_control (in) == 1)
		return (1);
	return (0);
}

int	ft_argm_control(t_dat *in)
{
	if (in->nph == -1 || in->td == -1 || in->te == -1 || in->ts == -1
		|| in->ne[0] == -1)
	{
		write (1, "No number in arguments\n", 23);
		free (in->ne);
		return (1);
	}
	if (in->nph == -2 || in->td == -2 || in->te == -2 || in->ts == -2
		|| in->ne[0] == -2)
	{
		write (1, "Number exceeded limits\n", 23);
		free (in->ne);
		return (1);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	int			c;
	long int	n;

	c = 0;
	i = -1;
	n = 0;
	while (str[c] != 00)
		c++;
	while (++i < c)
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
	}
	i = -1;
	while (++i < c)
		n = (n * 10) + (str[i] - '0');
	if (n < -2147483648 || n > 2147483647)
		return (-2);
	return (n);
}

void	ft_free_in(t_dat *in)
{
	if (in->fork != NULL)
		free (in->fork);
	if (in->mutex != NULL)
		free (in->mutex);
	if (in->ne != NULL)
		free (in->ne);
}

void	ft_free_phil(t_sphilo **phil, pthread_t *t)
{
	int	i;
	int	j;

	i = -1;
	j = phil[0]->in->nph;
	if (phil != NULL)
	{
		while (++i < j)
			free (phil[i]);
		free (phil);
	}
	if (t != NULL)
		free (t);
}

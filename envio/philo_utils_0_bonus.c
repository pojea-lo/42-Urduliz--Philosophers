/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_0_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 07:56:18 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/06/07 07:56:20 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_argm_input(int argc, char *argv[], t_dat *in)
{
	in->nph = ft_atoi (argv[1]);
	if (in->nph == 0)
	{
		write (1, "Number of philo equal to 0\n", 27);
		return (1);
	}
	in->fork = in->nph;
	in->td = ft_atoi (argv[2]);
	in->te = ft_atoi (argv[3]);
	in->ts = ft_atoi (argv[4]);
	in->id = 0;
	in->sp = 0;
	in->se = 0;
	in->sem = 0;
	in->sw = 0;
	in->ss = 0;
	in->sd = 2;
	in->i = -1;
	if (argc == 5)
		in->ne = -3;
	else
		in->ne = ft_atoi (argv[5]);
	if (ft_argm_control (in) == 1)
		return (1);
	return (0);
}

int	ft_argm_control(t_dat *in)
{
	if (in->nph == -2 || in->td == -2 || in->te == -2 || in->ts == -2
		|| in->ne == -2)
	{
		write (1, "Number exceeded limits\n", 23);
		return (1);
	}
	if (in->nph == -1 || in->td == -1 || in->te == -1 || in->ts == -1
		|| in->ne == -1)
	{
		write (1, "No number in arguments\n", 23);
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

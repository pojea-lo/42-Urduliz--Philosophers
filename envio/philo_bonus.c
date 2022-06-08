/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 07:54:56 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/06/07 07:54:58 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	in.spf = 0;
	if (ft_start (&in) == 1)
		return (1);
	return (0);
}

int	ft_start(t_dat *in)
{
	pid_t	*pid;
	int		i;

	i = -1;
	pid = (pid_t *) malloc(sizeof(pid_t) * in->nph);
	if (pid == NULL)
	{
		free (pid);
		return (1);
	}
	if (ft_start_two (pid, in) == 1)
	{
		free (pid);
		return (1);
	}
	free (pid);
	return (0);
}

//int	ft_start_two(pthread_t *t, t_sphilo **phil, t_dat *in)
int	ft_start_two(pid_t *pid, t_dat *in)
{
	int			i;

	i = -1;
	sem_unlink("mspf");
	sem_unlink("died");
	sem_unlink("semfork");
	in->mspf = sem_open ("mspf", O_CREAT | O_EXCL, 0644, 1);
	in->died = sem_open ("died", O_CREAT | O_EXCL, 0644, 1);
	in->semfork = sem_open ("semfork", O_CREAT | O_EXCL, 0644, in->nph);
	in->tstart = ft_time(0);
	while (++i < in->nph)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{	
			in->id = i;
			if (ft_create(in) == 1)
				return (1);
		}
		else if (pid[i] < 0)
			return (1);
	}
	ft_kill(in, pid);
	return (0);
}

void	ft_kill(t_dat *in, pid_t *pid)
{
	int	i;
	int	status;

	waitpid(-1, &status, 0);
	usleep ((in->te * 2 + in->ts) * 1000);
	if (status != 0)
	{
		i = -1;
		sem_wait (in->died);
		while (++i < in->nph)
			kill(pid[i], SIGKILL);
		sem_post (in->died);
	}
	sem_close (in->semfork);
	sem_close (in->mspf);
}

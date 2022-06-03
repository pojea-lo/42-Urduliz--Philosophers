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
	sem_unlink("mspf");
	sem_unlink("semfork");
//	system ("leaks bonus_philo");
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
int	ft_start_two(pid_t *pid,  t_dat *in)
{
	int			i;

	i = -1;
	sem_unlink("mspf");//para poder llamarlo luego en cada fork
	sem_unlink("died");//para poder llamarlo luego en cada fork
	sem_unlink("semfork");
	in->mspf = sem_open ("mspf", O_CREAT | O_EXCL, 0644, 1);//inicio los semaforos
	in->died = sem_open ("died", O_CREAT | O_EXCL, 0644, 1);//inicio los semaforos
	in->semfork = sem_open ("semfork", O_CREAT | O_EXCL, 0644, in->nph);
	in->tstart = ft_time(0);
	while (++i < in->nph)
	{
		pid[i] = fork();
//		printf ("el tiempo: %ld\n", ft_time(in->tstart));
		if (pid[i] == 0)//el proceso hijo
		{	
			in->id = i;
			if (ft_create(in) == 1)//, in->id) == 1)
				return (1);
		}
		else if (pid[i] < 0)//el fork ha dado error
			return (1);
	}
	ft_kill(in, pid);
	return (0);
}
	
void	ft_kill(t_dat *in, pid_t *pid)
{
	int	k;
	int	status;

	waitpid(-1, &status, 0);
	sem_wait (in->died);
	if (status != 0)
	{
		k = -1;
		while (++k < in->nph)
		{
			printf ("muerto el proceso %d\n", k);
			kill(pid[k], SIGKILL);
		}
	}

//	sem_close (in->semfork);//cierro los semaforos
//	sem_close (in->mspf);
}

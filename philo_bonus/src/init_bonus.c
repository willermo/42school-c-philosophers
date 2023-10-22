/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:54:48 by doriani           #+#    #+#             */
/*   Updated: 2023/10/20 03:55:40 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	start_philosopher(int i, t_ruleset *ruleset)
{
	pid_t		pid;
	t_philo		philosopher;

	pid = fork();
	if (pid == -1)
		exit (thread_error);
	if (pid > 0)
	{
		ruleset->philosophers[i] = pid;
		return ;
	}
	philosopher.ruleset = ruleset;
	philosopher.id = i;
	philosopher.eating = 0;
	philosopher.meals_eaten = 0;
	philosopher.exitus = ruleset->starting_time + ruleset->time_to_die;
	free(philosopher.ruleset->philosophers);
	philosopher.ruleset->philosophers = NULL;
	routine(&philosopher);
}

void	start_philosophers(t_ruleset *ruleset)
{
	int		i;
	int		n;

	n = ruleset->number_of_philosophers;
	i = 1;
	ruleset->starting_time = get_time();
	while (getpid() == ruleset->philosophers[0] && i <= n)
		start_philosopher(i++, ruleset);
}

t_exitcode	init_ruleset(char **argv, t_ruleset *ruleset, t_exitcode *code)
{
	int	n;

	n = (int)get_mseconds(argv[1]);
	ruleset->number_of_philosophers = n;
	ruleset->philosophers = (pid_t *)malloc((n + 1) * sizeof (pid_t));
	ruleset->philosophers[0] = getpid();
	ruleset->time_to_die = get_mseconds(argv[2]);
	ruleset->time_to_eat = get_mseconds(argv[3]);
	ruleset->time_to_sleep = get_mseconds(argv[4]);
	if (argv[5])
		ruleset->meals_count = (int)get_mseconds(argv[5]);
	else
		ruleset->meals_count = 0;
	ruleset->log = sem_open("/log", O_CREAT, 0644, 1);
	ruleset->forks = sem_open("/forks", O_CREAT, 0644, n);
	ruleset->lock = sem_open("/lock", O_CREAT, 0644, 1);
	return (*code);
}

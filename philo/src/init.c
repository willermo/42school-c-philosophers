/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:54:48 by doriani           #+#    #+#             */
/*   Updated: 2023/10/20 13:29:54 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philosopher(int id, t_ruleset *ruleset)
{
	t_philo	*philosopher;
	int		n;

	philosopher = (t_philo *)malloc(sizeof(t_philo));
	n = ruleset->number_of_philosophers;
	philosopher->id = id + 1;
	philosopher->ruleset = ruleset;
	philosopher->eating = 0;
	pthread_mutex_init(&philosopher->lock, NULL);
	if (philosopher->id % 2)
	{
		philosopher->first_fork = &ruleset->forks[(id + 1) % n];
		philosopher->second_fork = &ruleset->forks[id];
	}
	else
	{
		philosopher->first_fork = &ruleset->forks[id];
		philosopher->second_fork = &ruleset->forks[(id + 1) % n];
	}
	philosopher->meals_eaten = 0;
	return (philosopher);
}

t_exitcode	init_mutexes(t_ruleset *ruleset)
{
	int	i;
	int	n;

	if (pthread_mutex_init(&ruleset->log, NULL))
		return (error(MUTEX_ERROR, 1, mutex_error));
	i = 0;
	n = ruleset->number_of_philosophers;
	ruleset->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	while (i < n)
		if (pthread_mutex_init(&ruleset->forks[i++], NULL))
			return (error(FORK_ERROR, i, mutex_error));
	return (valid);
}

t_exitcode	init_philosophers(t_ruleset *ruleset)
{
	int		i;
	int		n;
	t_philo	*philosopher;

	n = ruleset->number_of_philosophers;
	ruleset->philosophers = (t_philo **) malloc(sizeof (t_philo *) * n);
	if (ruleset->philosophers == NULL)
		return (error(ALLOC_ERROR, 1, alloc_error));
	i = 0;
	while (i < n)
	{
		philosopher = create_philosopher(i, ruleset);
		ruleset->philosophers[i++] = philosopher;
	}
	return (valid);
}

t_exitcode	init_params(char **argv, t_ruleset *ruleset, t_exitcode *code)
{
	ruleset->number_of_philosophers = (int)get_mseconds(argv[1]);
	ruleset->starting_time = -1;
	ruleset->time_to_die = get_mseconds(argv[2]);
	ruleset->time_to_eat = get_mseconds(argv[3]);
	ruleset->time_to_sleep = get_mseconds(argv[4]);
	if (argv[5])
		ruleset->meals_count = (int)get_mseconds(argv[5]);
	else
		ruleset->meals_count = 0;
	ruleset->stop_simulation = 0;
	ruleset->finished = 0;
	*code += init_mutexes(ruleset);
	if (*code)
		return (*code);
	*code += init_philosophers(ruleset);
	return (*code);
}

t_exitcode	join_philosophers(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		if (pthread_join(ruleset->threads[i], NULL))
			return (error(JOIN_ERROR, i, join_error));
		i++;
	}
	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		if (pthread_join(ruleset->philosophers[i]->reaper, NULL))
			return (error(JOIN_ERROR, i, join_error));
		i++;
	}
	if (ruleset->meals_count)
		if (pthread_join(ruleset->restaurant, NULL))
			return (error(JOIN_ERROR, 0, join_error));
	return (valid);
}

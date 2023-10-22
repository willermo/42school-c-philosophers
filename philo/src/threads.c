/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:12:40 by doriani           #+#    #+#             */
/*   Updated: 2023/10/22 10:38:01 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_exitcode	start_philosophers(t_ruleset *ruleset)
{
	int			i;
	int			n;

	i = 0;
	n = ruleset->number_of_philosophers;
	ruleset->threads = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (ruleset->meals_count)
	{
		if (pthread_create(&ruleset->restaurant, NULL, &maitre, \
			(void *)ruleset))
			return (error(THREAD_ERROR, 0, thread_error));
	}
	ruleset->starting_time = get_time();
	while (i < n)
	{
		if (pthread_create(&ruleset->threads[i], NULL, \
				&routine, (void *)ruleset->philosophers[i]))
			return (error(THREAD_ERROR, i, thread_error));
		i++;
	}
	return (valid);
}

void	*maitre(void *ruleset)
{
	t_ruleset	*table;

	table = (t_ruleset *) ruleset;
	pthread_mutex_lock(&table->log);
	while (!table->stop_simulation)
	{
		pthread_mutex_unlock(&table->log);
		if (table->finished >= table->number_of_philosophers)
		{
			pthread_mutex_lock(&table->log);
			table->stop_simulation = 1;
			pthread_mutex_unlock(&table->log);
		}
		pthread_mutex_lock(&table->log);
	}
	pthread_mutex_unlock(&table->log);
	return (NULL);
}

void	*reap(void *philosopher)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->ruleset->log);
	while (!philo->ruleset->stop_simulation)
	{
		pthread_mutex_unlock(&philo->ruleset->log);
		time = get_time();
		pthread_mutex_lock(&philo->lock);
		if (time > philo->exitus && !philo->eating)
			msg_log(time, philo, DIED_LOG, die_message);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->ruleset->log);
	}
	pthread_mutex_unlock(&philo->ruleset->log);
	return (NULL);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->exitus = philo->ruleset->starting_time + philo->ruleset->time_to_die;
	pthread_create(&philo->reaper, NULL, &reap, philosopher);
	pthread_mutex_lock(&philo->ruleset->log);
	while (philo->ruleset->stop_simulation == 0)
	{
		pthread_mutex_unlock(&philo->ruleset->log);
		take_forks(philo);
		eat(philo);
		digest(philo);
		think(philo);
		pthread_mutex_lock(&philo->ruleset->log);
	}
	pthread_mutex_unlock(&philo->ruleset->log);
	return (NULL);
}

t_exitcode	lonely_boy(t_ruleset *ruleset)
{
	ruleset->threads = (pthread_t *)malloc(sizeof(pthread_t));
	ruleset->starting_time = get_time();
	if (pthread_create(&ruleset->threads[0], NULL, &routine, \
		(void *)ruleset->philosophers[0]))
	{
		printf("got here\n");
		return (error(THREAD_ERROR, 1, thread_error));
	}
	pthread_detach(ruleset->threads[0]);
	while (ruleset->stop_simulation == 0)
		better_usleep(0);
	cleanup(ruleset);
	return (valid);
}

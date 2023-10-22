/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:26:47 by doriani           #+#    #+#             */
/*   Updated: 2023/10/22 10:38:02 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	long	time;

	sem_wait(philo->ruleset->forks);
	msg_log(get_time(), philo, FORK_LOG, default_message);
	sem_wait(philo->ruleset->forks);
	msg_log(get_time(), philo, FORK_LOG, default_message);
	time = get_time();
	sem_wait(philo->ruleset->lock);
	philo->eating = 1;
	msg_log(time, philo, EAT_LOG, eat_message);
	philo->exitus = time + philo->ruleset->time_to_die;
	sem_post(philo->ruleset->lock);
	philo->meals_eaten++;
	better_usleep(philo->ruleset->time_to_eat);
	sem_post(philo->ruleset->forks);
	sem_post(philo->ruleset->forks);
	if (philo->ruleset->meals_count \
	&& philo->meals_eaten >= philo->ruleset->meals_count)
		exit(0);
	philo->eating = 0;
}

void	digest(t_philo *philo)
{
	long	time;

	time = get_time();
	msg_log(time, philo, SLEEP_LOG, default_message);
	better_usleep(philo->ruleset->time_to_sleep);
}

void	think(t_philo *philo)
{
	long	time;

	time = get_time();
	msg_log(time, philo, THINK_LOG, default_message);
}

void	*reap(void *philosopher)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)philosopher;
	while (1)
	{
		time = get_time();
		sem_wait(philo->ruleset->lock);
		if (time > philo->exitus && !philo->eating)
		{
			msg_log(time, philo, DIED_LOG, die_message);
			sem_close(philo->ruleset->forks);
			sem_close(philo->ruleset->log);
			sem_close(philo->ruleset->lock);
			exit(1);
		}
		sem_post(philo->ruleset->lock);
	}
}

void	routine(t_philo *philosopher)
{
	pthread_create(&philosopher->reaper, NULL, &reap, philosopher);
	pthread_detach(philosopher->reaper);
	while (1)
	{
		eat(philosopher);
		digest(philosopher);
		think(philosopher);
	}
}

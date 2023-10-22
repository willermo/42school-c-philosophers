/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:26:47 by doriani           #+#    #+#             */
/*   Updated: 2023/10/22 10:39:17 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->lock);
	time = get_time();
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock);
	msg_log(time, philo, EAT_LOG, eat_message);
	philo->exitus = time + philo->ruleset->time_to_die;
	philo->meals_eaten++;
	better_usleep(philo->ruleset->time_to_eat);
	drop_forks(philo);
	if (philo->ruleset->meals_count)
		if (philo->meals_eaten >= philo->ruleset->meals_count)
			philo->ruleset->finished++;
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
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

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	msg_log(get_time(), philo, FORK_LOG, default_message);
	pthread_mutex_lock(philo->second_fork);
	msg_log(get_time(), philo, FORK_LOG, default_message);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

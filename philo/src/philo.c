/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:45:45 by doriani           #+#    #+#             */
/*   Updated: 2023/10/20 13:30:26 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static t_exitcode	usage(void)
{
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (args_count);
}

void	msg_log(long timestamp, t_philo *philo, char *msg, t_msg type)
{
	char	*color;

	if (type == default_message)
		color = RESET;
	else if (type == eat_message)
		color = GREEN;
	else if (type == die_message)
		color = RED;
	else if (type == debug_message)
		color = RESET;
	timestamp -= philo->ruleset->starting_time;
	pthread_mutex_lock(&philo->ruleset->log);
	if (!philo->ruleset->stop_simulation)
	{
		printf("%s%ld %d %s%s\n", color, timestamp, philo->id, msg, RESET);
		if (type == die_message)
			philo->ruleset->stop_simulation = 1;
	}
	pthread_mutex_unlock(&philo->ruleset->log);
}

t_exitcode	error(char *message, int param, t_exitcode error_code)
{
	printf("%s %d\n", message, param);
	return (error_code);
}

void	cleanup(t_ruleset *ruleset)
{
	int	i;
	int	n;

	n = ruleset->number_of_philosophers;
	i = 0;
	while (i < n)
		pthread_mutex_destroy(&ruleset->forks[i++]);
	free(ruleset->forks);
	ruleset->forks = NULL;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&ruleset->philosophers[i]->lock);
		free(ruleset->philosophers[i]);
		i++;
	}
	free(ruleset->threads);
	free(ruleset->philosophers);
	pthread_mutex_destroy(&ruleset->log);
	ruleset->philosophers = NULL;
}

int	main(int argc, char **argv)
{
	t_exitcode	exit_code;
	t_ruleset	ruleset;

	exit_code = valid;
	if (argc < 5 || argc > 6)
		return (usage());
	validate_input(argv, &exit_code);
	if (exit_code)
		return (exit_code);
	if (init_params(argv, &ruleset, &exit_code))
		return (exit_code);
	if (ruleset.number_of_philosophers == 1)
		return (lonely_boy(&ruleset));
	exit_code = start_philosophers(&ruleset);
	if (exit_code == valid)
		exit_code = join_philosophers(&ruleset);
	cleanup(&ruleset);
	return (exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:55:56 by doriani           #+#    #+#             */
/*   Updated: 2023/10/20 04:22:42 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		color = YELLOW;
	timestamp -= philo->ruleset->starting_time;
	sem_wait(philo->ruleset->log);
	printf("%s%ld %d %s%s\n", color, timestamp, philo->id, msg, RESET);
	if (type != die_message)
		sem_post(philo->ruleset->log);
}

t_exitcode	error(char *message, int param, t_exitcode error_code)
{
	printf("%s %d\n", message, param);
	return (error_code);
}

void	cleanup(t_ruleset *ruleset)
{
	sem_close(ruleset->forks);
	sem_close(ruleset->log);
	sem_close(ruleset->lock);
	if (ruleset->philosophers)
	{
		sem_unlink("/forks");
		sem_unlink("/log");
		sem_unlink("/lock");
		free(ruleset->philosophers);
	}
}

static void	leave_table(t_ruleset ruleset)
{
	int	i;

	i = 1;
	while (i <= ruleset.number_of_philosophers)
		kill(ruleset.philosophers[i++], SIGKILL);
}

int	main(int argc, char **argv)
{
	t_exitcode	exit_code;
	t_ruleset	ruleset;
	int			status;

	exit_code = valid;
	if (argc < 5 || argc > 6)
		return (usage());
	validate_input(argv, &exit_code);
	if (exit_code)
		return (exit_code);
	if (init_ruleset(argv, &ruleset, &exit_code))
		return (exit_code);
	start_philosophers(&ruleset);
	if (getpid() == ruleset.philosophers[0])
		while (waitpid(0, &status, 0) > -1)
			if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
				leave_table(ruleset);
	cleanup(&ruleset);
	return (exit_code);
}

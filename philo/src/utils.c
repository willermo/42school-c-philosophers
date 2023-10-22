/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:59:56 by doriani           #+#    #+#             */
/*   Updated: 2023/10/09 12:20:28 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n' \
	|| ch == '\r' || ch == '\t' || ch == '\v')
		return (1);
	return (0);
}

long	get_mseconds(const char *nptr)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
	{
		nptr++;
	}
	else if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	result *= sign;
	return (result);
}

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	better_usleep(long wait_time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < wait_time)
		usleep((time_t)10);
}

long	get_exitus(t_philo *philo)
{
	return (get_time() + philo->ruleset->time_to_die);
}

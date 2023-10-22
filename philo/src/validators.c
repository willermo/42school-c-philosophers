/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:08:35 by doriani           #+#    #+#             */
/*   Updated: 2023/10/06 00:31:40 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	validate_input(char **argv, t_exitcode *exit_code)
{
	if (get_mseconds(argv[1]) < 1)
	{
		printf("Error: number of philosophers must be greater than 0\n");
		*exit_code += number_of_philosophers;
	}
	if (get_mseconds(argv[2]) < 1)
	{
		printf("Error: time to die must be greater than 0\n");
		*exit_code += time_to_die;
	}
	if (get_mseconds(argv[3]) < 1)
	{
		printf("Error: time to eat must be greater than 0\n");
		*exit_code += time_to_eat;
	}
	if (get_mseconds(argv[4]) < 1)
	{
		printf("Error: time to sleep must be greater than 0\n");
		*exit_code += time_to_sleep;
	}
	if (argv[5] && get_mseconds(argv[5]) < 1)
	{
		printf("Error: meals count must be greater than 0\n");
		*exit_code += meals_count;
	}
}

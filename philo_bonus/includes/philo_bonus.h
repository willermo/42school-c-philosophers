/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:26:35 by doriani           #+#    #+#             */
/*   Updated: 2023/10/20 04:12:04 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdint.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define FORK_LOG 		"has taken a fork"
# define EAT_LOG		"is eating"
# define SLEEP_LOG		"is sleeping"
# define THINK_LOG		"is thinking"
# define DIED_LOG		"died"
# define DROP_LOG		"dropped forks"
# define ALLOC_ERROR	"Error during memory allocation for philosophers"
# define MUTEX_ERROR	"Mutex initialization failure on mutex"
# define FORK_ERROR		"Semaphore initialization failure on fork"
# define THREAD_ERROR	"Thread initialization failure on thread"
# define JOIN_ERROR		"Thread join failure on thread"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define CYAN			"\033[0;36m"
# define RESET			"\033[0m"

typedef enum e_exitcode
{
	valid = 0,
	args_count = 1,
	number_of_philosophers = 2,
	time_to_die = 4,
	time_to_eat = 8,
	time_to_sleep = 16,
	meals_count = 32,
	mutex_error = 64,
	fork_error = 128,
	thread_error = 256,
	join_error = 512,
	alloc_error = 1024
}	t_exitcode;

typedef enum e_message_type
{
	default_message,
	eat_message,
	die_message,
	debug_message
}	t_msg;

typedef struct s_philo	t_philo;

typedef struct s_ruleset
{
	int				number_of_philosophers;
	long			starting_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_count;
	sem_t			*forks;
	sem_t			*log;
	sem_t			*lock;
	pid_t			*philosophers;
}	t_ruleset;

typedef struct s_philo
{
	t_ruleset		*ruleset;
	int				id;
	int				eating;
	int				meals_eaten;
	long			exitus;
	pthread_t		reaper;
}	t_philo;

//philo_bonus.c
void			msg_log(long timestamp, t_philo *philo, char *msg, t_msg type);
t_exitcode		error(char *message, int param, t_exitcode error_code);
void			cleanup(t_ruleset *ruleset);
// validators_bonus.c
t_exitcode		usage(void);
void			validate_input(char **argv, t_exitcode *exit_code);
// utils_bonus.c
long			get_mseconds(const char *nptr);
long			get_time(void);
void			better_usleep(long wait_time);
//	init_bonus.c
void			start_philosophers(t_ruleset *ruleset);
t_exitcode		init_ruleset(char **argv, t_ruleset *ruleset, t_exitcode *code);
//	routine_bonus.c
void			eat(t_philo *philo);
void			digest(t_philo *philo);
void			think(t_philo *philo);
void			*reap(void *philosopher);
void			routine(t_philo *philosopher);
#endif

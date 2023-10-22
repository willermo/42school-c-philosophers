/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:50:37 by doriani           #+#    #+#             */
/*   Updated: 2023/10/20 13:30:05 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

# define FORK_LOG 		"has taken a fork"
# define EAT_LOG		"is eating"
# define SLEEP_LOG		"is sleeping"
# define THINK_LOG		"is thinking"
# define DIED_LOG		"died"
# define DROP_LOG		"dropped forks"
# define ALLOC_ERROR	"Error during memory allocation for philosophers"
# define MUTEX_ERROR	"Mutex initialization failure on mutex"
# define FORK_ERROR		"Mutex initialization failure on fork"
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
	thread_error = 128,
	join_error = 256,
	alloc_error = 512
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
	int				stop_simulation;
	int				finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log;
	pthread_t		*threads;
	pthread_t		restaurant;
	t_philo			**philosophers;
}	t_ruleset;

typedef struct s_philo
{
	int				id;
	pthread_t		reaper;
	t_ruleset		*ruleset;
	int				eating;
	pthread_mutex_t	lock;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				meals_eaten;
	long			exitus;
}	t_philo;

//philo.c
void			msg_log(long timestamp, t_philo *philo, char *msg, t_msg type);
t_exitcode		error(char *message, int param, t_exitcode error_code);
void			cleanup(t_ruleset *ruleset);
// validators.c
void			validate_input(char **argv, t_exitcode *exit_code);
// utils
long			get_mseconds(const char *nptr);
long			get_time(void);
void			better_usleep(long wait_time);
long			get_exitus(t_philo *philo);
//	init.c
t_philo			*create_philosopher(int n, t_ruleset *ruleset);
t_exitcode		init_mutexes(t_ruleset *ruleset);
t_exitcode		init_philosophers(t_ruleset *ruleset);
t_exitcode		init_params(char **argv, t_ruleset *ruleset, t_exitcode *code);
t_exitcode		join_philosophers(t_ruleset *ruleset);
//	threads.c
t_exitcode		start_philosophers(t_ruleset *ruleset);
void			*maitre(void *ruleset);
void			*reap(void *philosopher);
void			*routine(void *philosopher);
t_exitcode		lonely_boy(t_ruleset *ruleset);
//	routine.c
void			eat(t_philo *philo);
void			digest(t_philo *philo);
void			think(t_philo *philo);
void			take_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
#endif

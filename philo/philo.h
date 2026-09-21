/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:47:57 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/21 17:17:54 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

// Output messages
# define CHOPSTICK	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DEATH		"died"

typedef struct s_general_data
{
	int					n_philosophers;
	int64_t				time_to_die;
	int64_t				time_to_eat;
	int64_t				time_to_sleep;
	int					minimum_meals;
	int					alive;
	int64_t				sim_start;
	bool				someone_died;
	int					philos_ate_enough;
	bool				simulation_end;
	pthread_mutex_t		print;
	pthread_mutex_t		theone;
}		t_general_data;

typedef struct s_philo_data
{
	pthread_t		thread_id;
	int				id;
	int64_t			start_of_last_meal;
	int				times_eaten;
	pthread_mutex_t	chopstick;
	pthread_mutex_t	*right_chopstick;
	t_general_data	*data;
}		t_philo_data;

// general
int		initiate_general_data(char **av, t_general_data *data);
int		initiate_mutex(t_general_data *data);
int		initiate_philosophers(t_general_data *data, t_philo_data **p_data);
void	*philosopher(void *arg);
int		eating(t_philo_data *p_data);
int		sleeping(t_philo_data *p_data);
int		thinking(t_philo_data *p_data);

// cleanups
void	cleanup(t_general_data *data, t_philo_data *p_data);
void	destroy_mutexes(t_general_data *data, t_philo_data *p_data);
void	join_threads(t_philo_data *p_data, int philo_n);

//thinking_helpers
int		calc_think_time(t_general_data *data, t_philo_data *p_data,
			int64_t	remaining);
int		try_to_pick_up_chopsticks(t_philo_data *p_data);

// helpers
int		malloc_and_initialize(void **data, size_t size);
int64_t	get_time(void);
int		check_for_end(t_philo_data *p_data);
int64_t	time_since_start(t_philo_data *p_data);
int		print_msg(char *msg, t_philo_data *p_data);
void	flexsleep(int64_t max_phase_length, int64_t start_of_phase);
int64_t	time_since_start(t_philo_data *p_data);
int		grab_chopstick(pthread_mutex_t *chopstick, t_philo_data *p_data);
int		grab_chopsticks_even(t_philo_data *p_data);
int		grab_chopsticks_uneven(t_philo_data *p_data);
void	drop_chopsticks(t_philo_data *p_data);

// if conditions
int		even_philos(t_philo_data *p_data);
int		uneven_philos_without_last(t_philo_data *p_data);

#endif
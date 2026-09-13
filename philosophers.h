/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:47:57 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 12:04:59 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_general_data
{
	int					n_philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					minimum_meals;
	bool				someone_died;
	int					philos_ate_enough;
	bool				simulation_end;
}		t_general_data;

typedef struct s_mutex_thread_data
{
	pthread_mutex_t		print;
	bool				print_initailized;
	pthread_mutex_t		start;
	bool				start_initailized;
	pthread_mutex_t		died;
	bool				died_initailized;
	pthread_mutex_t		ate_enough;
	bool				ate_enough_initailized;
	pthread_mutex_t		end;
	bool				end_initailized;
	pthread_mutex_t		*chopsticks;
	bool				*chopsticks_initialized;
	pthread_t			*id;
	bool				*thread_created;
}		t_mutex_thread_data;

typedef struct s_philo_data
{
	int				id;
	long long		start_of_last_meal;
	int				times_eaten;
	pthread_mutex_t	*left_chopstick;
	pthread_mutex_t	*right_chopstick;
	pthread_mutex_t	*print;
	pthread_mutex_t	*start;
	pthread_mutex_t	*died;
	pthread_mutex_t	*ate_enough;
	pthread_mutex_t	*end;
	t_general_data	*data;
}		t_philo_data;


int	initiate_general_data(char **av, t_general_data *data);


#endif
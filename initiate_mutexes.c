/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mutexes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 12:10:30 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 12:33:42 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_mutex(pthread_mutex_t *mutex, bool *initialized);
static int	create_chopsticks(t_mutex_thread_data *mt_data,
	t_general_data *data);

int	initiate_mutexes(t_mutex_thread_data *mt_data, t_general_data *data)
{
	memset(mt_data, 0, sizeof(t_mutex_thread_data));
	if (create_mutex(&mt_data->print, &mt_data->print_initailized))
		return (1);
	if (create_mutex(&mt_data->start, &mt_data->start_initailized))
		return (1);
	if (create_mutex(&mt_data->died, &mt_data->died_initailized))
		return (1);
	if (create_mutex(&mt_data->ate_enough, &mt_data->ate_enough_initailized))
		return (1);
	if (create_mutex(&mt_data->end, &mt_data->end_initailized))
		return (1);
	if (create_chopsticks(mt_data, data))
		return (1);
	return (0);
}

static int	create_mutex(pthread_mutex_t *mutex, bool *initialized)
{
	if (pthread_mutex_init(mutex, NULL))
		return (printf("Error: Unable to open mutex"), 1);
	*initialized = true;
	return (0);
}

static int	create_chopsticks(t_mutex_thread_data *mt_data,
	t_general_data *data)
{
	int	i;
	
	mt_data->chopsticks_initialized = malloc(sizeof(bool) *
		data->n_philosophers);
	if (!mt_data->chopsticks_initialized)
		return (printf("Error: Malloc failed"), 1);
	memset(mt_data->chopsticks_initialized, 0, sizeof(bool) *
		data->n_philosophers);
	mt_data->chopsticks = malloc(sizeof(pthread_mutex_t) *
		data->n_philosophers);
	if (!mt_data->chopsticks)
		return (printf("Error: Malloc failed"), 1);
	i = 0;
	while (i < data->n_philosophers)
	{
		if (pthread_mutex_init(&mt_data->chopsticks[i], NULL))
			return (printf("Error: Unable to open mutex"), 1);
		mt_data->chopsticks_initialized[i] = true;
		i++;
	}
    return (0);
}

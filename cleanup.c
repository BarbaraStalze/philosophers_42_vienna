/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 12:40:09 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 12:49:15 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	close_n_free_mutextes(t_mutex_thread_data *mt_data,
			t_general_data *data);
static void	close_n_free_mutex_array(pthread_mutex_t *mutex, bool *mutex_initialized,
            t_general_data *data);

void	cleanup(t_mutex_thread_data *mt_data,
			t_general_data *data)
{
	close_n_free_mutextes(mt_data, data);
	end_threads(mt_data, data);
}

static void	close_n_free_mutextes(t_mutex_thread_data *mt_data,
			t_general_data *data)
{
	if (mt_data->print_initailized == true)
		pthread_mutex_destroy(&mt_data->print);
	if (mt_data->start_initailized == true)
		pthread_mutex_destroy(&mt_data->start);
	if (mt_data->died_initailized == true)
		pthread_mutex_destroy(&mt_data->died);
	if (mt_data->ate_enough_initailized == true)
		pthread_mutex_destroy(&mt_data->ate_enough);
	if (mt_data->end_initailized == true)
		pthread_mutex_destroy(&mt_data->end);
    close_n_free_mutex_array(mt_data->chopsticks,
		mt_data->chopsticks_initialized, data);
}

static void	close_n_free_mutex_array(pthread_mutex_t *mutex, bool *mutex_initialized,
            t_general_data *data)
{
    int i;

    i = 0;
	if (mutex && mutex_initialized)
	{
		while (i < data->n_philosophers)
		{
			if (mutex_initialized[i] == true)
				pthread_mutex_destroy(&(mutex[i]));
			i++;
		}
		free(mutex_initialized);
        mutex_initialized = NULL;
	}
    if (mutex_initialized)
    {
        free(mutex_initialized);
        mutex_initialized = NULL;
    }
    if (mutex)
    {
        free(mutex);
        mutex = NULL;
    }
}

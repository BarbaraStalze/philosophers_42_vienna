/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 12:40:09 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/15 15:27:32 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	close_n_free_mutextes(t_mutex_thread_data *mt_data,
// 				t_general_data *data);
// static void	close_n_free_mutex_array(pthread_mutex_t *mutex,
// 				bool *mutex_initialized, t_general_data *data);

// void	cleanup(t_general_data *data, t_philo_data *p_data, int i)
// {
// 	pthread_mutex_lock(data->start_o_end);
// 	data->simulation_end = true;
// 	pthread_mutex_unlock(data->start_o_end);
// 	pthread_mutex_destroy(data->)
// 	close_n_free_mutextes(data);
// 	free_thread_p_data(mt_data, p_data);
// }

// static void	close_n_free_mutextes(t_mutex_thread_data *mt_data,
// 			t_general_data *data)
// {
// 	if (mt_data->print_initailized == true)
// 		pthread_mutex_destroy(&mt_data->print);
// 	if (mt_data->start_initailized == true)
// 		pthread_mutex_destroy(&mt_data->start);
// 	if (mt_data->died_initailized == true)
// 		pthread_mutex_destroy(&mt_data->died);
// 	if (mt_data->ate_enough_initailized == true)
// 		pthread_mutex_destroy(&mt_data->ate_enough);
// 	if (mt_data->end_initailized == true)
// 		pthread_mutex_destroy(&mt_data->end);
// 	close_n_free_mutex_array(mt_data->chopsticks,
// 		mt_data->chopsticks_initialized, data);
// }

// static void	close_n_free_mutex_array(pthread_mutex_t *mutex,
// 				bool *mutex_initialized, t_general_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (mutex && mutex_initialized)
// 	{
// 		while (i < data->n_philosophers)
// 		{
// 			if (mutex_initialized[i] == true)
// 				pthread_mutex_destroy(&(mutex[i]));
// 			i++;
// 		}
// 		free(mutex_initialized);
// 		mutex_initialized = NULL;
// 	}
// 	if (mutex_initialized)
// 	{
// 		free(mutex_initialized);
// 		mutex_initialized = NULL;
// 	}
// 	if (mutex)
// 	{
// 		free(mutex);
// 		mutex = NULL;
// 	}
// }

// void	free_thread_p_data(t_mutex_thread_data *mt_data, t_philo_data *p_data)
// {
// 	free(p_data);
// 	p_data = NULL;
// 	free(mt_data->id);
// 	mt_data->id = NULL;
// 	free(mt_data->thread_created);
// 	mt_data->thread_created = NULL;
// }

void	destroy_mutexes(t_general_data *data, t_philo_data *p_data)
{
	int i;

	i = 0;
	while (i < data->n_philosophers)
	{
		pthread_mutex_destroy(&p_data[i].chopstick);
		i++;
	}
	pthread_mutex_destroy(&data->start_o_end);
}

void	cleanup(t_general_data *data, t_philo_data *p_data)
{
	destroy_mutexes(data, p_data);
	free(p_data);
}

void	join_threads(t_philo_data *p_data, int philo_n)
{
	int	i;

	i = 0;
	while (i < philo_n)
	{
		pthread_join(p_data[i].thread_id, NULL);
		i++;
	}
}

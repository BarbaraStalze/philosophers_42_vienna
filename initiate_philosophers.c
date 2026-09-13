/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_philosophers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:06:37 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 16:24:26 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_threads(t_mutex_thread_data *mt_data, t_general_data *data,
				t_philo_data *p_data);
static void	add_data(t_mutex_thread_data *mt_data, t_general_data *data,
				t_philo_data *p_data, int i);

int	initiate_philosophers(t_mutex_thread_data *mt_data, t_general_data *data)
{
	t_philo_data	*p_data;

	p_data = NULL;
	if (malloc_and_initialize((void **)(&p_data), sizeof(t_philo_data) *
		data->n_philosophers))
		return (1);
	if (malloc_and_initialize((void **)(&mt_data->id), sizeof(pthread_t) *
		data->n_philosophers))
		return (free_thread_p_data(mt_data, p_data), 1);
	if (malloc_and_initialize((void **)(&mt_data->thread_created), sizeof(bool)
		* data->n_philosophers))
		return (free_thread_p_data(mt_data, p_data), 1);
	if (create_threads(mt_data, data, p_data))
		return (free_thread_p_data(mt_data, p_data),
			join_threads(mt_data, data), 1);
	return (0);
}

static int	create_threads(t_mutex_thread_data *mt_data, t_general_data *data,
				t_philo_data *p_data)
{
	int	i;
	
	i = 0;
	while (i < data->n_philosophers)
	{
		add_data(mt_data, data, p_data, i);
		if (!pthread_create(&mt_data->id[i], NULL, philosopher, (void *)&p_data[i]))
			mt_data->thread_created[i] = true;
		if (mt_data->thread_created[i] == false)
		{
			pthread_mutex_lock(&mt_data->print);
			printf("Error: Thread %d could not be created\n", i + 1);
			pthread_mutex_unlock(&mt_data->print);
			pthread_mutex_lock(&mt_data->end);
			p_data->data->simulation_end = true;
			pthread_mutex_unlock(&mt_data->end);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_data(t_mutex_thread_data *mt_data, t_general_data *data,
				t_philo_data *p_data, int i)
{
	p_data[i].id = i + 1;
	p_data[i].left_chopstick = &mt_data->chopsticks[i];
	if (i + 1 == data->n_philosophers)
		p_data[i].right_chopstick = &mt_data->chopsticks[0];
	else
		p_data[i].right_chopstick = &mt_data->chopsticks[i + 1];
	p_data[i].print = &mt_data->print;
	p_data[i].start = &mt_data->start;
	p_data[i].died = &mt_data->died;
	p_data[i].ate_enough = &mt_data->ate_enough;
	p_data[i].end = &mt_data->end;
	p_data[i].data = data;
}

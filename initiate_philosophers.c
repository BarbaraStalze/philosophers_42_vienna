/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_philosophers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:06:37 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/15 15:33:41 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_general_data *data,
				t_philo_data *p_data);
static int	initiate_chopsticks(t_philo_data *p_data, int philo_num);

int	initiate_philosophers(t_general_data *data,
		t_philo_data **p_data)
{
	if (malloc_and_initialize((void **)(p_data), sizeof(t_philo_data)
		* data->n_philosophers))
		return (1);
	// if (malloc_and_initialize((void **)(&mt_data->thread_created), sizeof(bool)
	// 	* data->n_philosophers))
	// 	return (free_thread_p_data(mt_data, p_data), 1);
	if (initiate_chopsticks(*p_data, data->n_philosophers))
		return (free(*p_data), *p_data = NULL, 1);
	if (create_threads(data, *p_data))
		return (free(*p_data), *p_data = NULL, 1);
	return (0);
}
void	link_philos(t_philo_data *p_data, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num - 1)
	{
		p_data[i].right_chopstick = &p_data[i + 1].chopstick;
		i++;
	}
	p_data[i].right_chopstick = &p_data[0].chopstick;
}
				
static int initiate_chopsticks(t_philo_data *p_data, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_mutex_init(&p_data[i].chopstick, NULL))
			break ;
		i++;
		if (i == philo_num)
			return (link_philos(p_data, i), 0);
	}
	i--;
	while (i > 0)
	{
		pthread_mutex_destroy(&p_data[i].chopstick);
		i--;
	}
	return (1);
	
}

static int	create_threads(t_general_data *data,
				t_philo_data *p_data)
{
	int	i;

	i = 0;
	while (i < data->n_philosophers)
	{
		p_data[i].id = i + 1;
		p_data[i].data = data;
		if (pthread_create(&p_data[i].thread_id, NULL, philosopher,
				(void *)&p_data[i]))
			return (join_threads(p_data, i), 1);
		// if (mt_data->thread_created[i] == false)
		// {
		// 	pthread_mutex_lock(&mt_data->print);
		// 	printf("Error: Thread %d could not be created\n", i + 1);
		// 	pthread_mutex_unlock(&mt_data->print);
		// 	pthread_mutex_lock(&mt_data->end);
		// 	p_data->data->simulation_end = true;
		// 	pthread_mutex_unlock(&mt_data->end);
		// 	return (1);
		// }
		i++;
	}
	return (0);
}

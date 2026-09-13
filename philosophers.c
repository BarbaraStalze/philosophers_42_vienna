/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 14:48:31 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 15:02:17 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher(void *arg)
{
	t_philo_data *p_data;

	p_data = (t_philo_data *)arg;
	if (wait_for_all(p_data))
		return ;
	first_meal(p_data);
}

static int	wait_for_all(t_philo_data *p_data)
{
	int	check;

	check = 0;
	pthread_mutex_lock(p_data->start);
	p_data->data->alive++;
	if (p_data->data->alive == p_data->data->n_philosophers)
		p_data->data->sim_start = get_time();
	pthread_mutex_unlock(p_data->start);
	while (1)
	{
		pthread_mutex_lock(p_data->start);
		if (p_data->data->alive == p_data->data->n_philosophers)
		{
			p_data->start_of_last_meal = p_data->data->sim_start;
			check = 1;
		}
		pthread_mutex_unlock(p_data->start);
		if (check == 1)
			return (0);
		if (check_for_end(p_data))
			return (1);
		usleep(100);
	}
}

void	first_meal(t_philo_data *p_data)
{
	if (even_philos(p_data))
	{
		pthread_mutex_lock(p_data->left_chopstick);
		pthread_mutex_lock(p_data->right_chopstick);
	}
	else if (uneven_philos_without_last(p_data))
	{
		usleep((p_data->data->time_to_die * 1000) - 100);
		pthread_mutex_lock(p_data->right_chopstick);
		pthread_mutex_lock(p_data->left_chopstick);
	}
	else
	{
		usleep((p_data->data->time_to_die * 1000 * 2) - 100);
		pthread_mutex_lock(p_data->right_chopstick);
		pthread_mutex_lock(p_data->left_chopstick);
	}
}

// Even philosophers start by grabbing the left fork first and then the right,
// uneven philos grab the right fork first after sleeping almost the amount of
// time of time_to_eat. The last uneven philosopher in case of an uneven amount
// of philosophers waits almost twice the time_to_eat until grabbing forks.


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
	if (first_meal(p_data))
		return ;
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

static int	first_meal(t_philo_data *p_data)
{
	if (even_philos(p_data))
	{
		pthread_mutex_lock(p_data->left_chopstick);
		pthread_mutex_lock(p_data->right_chopstick);
	}
	else if (uneven_philos_without_last(p_data))
	{
		if (first_meal_wait(p_data, false))
			return (1);
		pthread_mutex_lock(p_data->right_chopstick);
		pthread_mutex_lock(p_data->left_chopstick);
	}
	else
	{
		if (first_meal_wait(p_data, true))
			return (1);
		pthread_mutex_lock(p_data->right_chopstick);
		pthread_mutex_lock(p_data->left_chopstick);
	}
	return (0);
}

// Even philosophers start by grabbing the left fork first and then the right,
// uneven philos grab the right fork first after sleeping almost the amount of
// time of time_to_eat. The last uneven philosopher in case of an uneven amount
// of philosophers waits almost twice the time_to_eat until grabbing forks.

int	first_meal_wait(t_philo_data *p_data, bool last)
{
	int64_t	remaining_time;

	if (last == false)
		remaining_time = p_data->data->time_to_eat;
	else
		remaining_time = p_data->data->time_to_eat * 2;
	while (remaining_time > 1)
	{
		if (check_for_end)
			return (1);
		flexsleep(remaining_time, p_data->data->sim_start);
		remaining_time = p_data->data->sim_start + p_data->data->time_to_eat - get_time();
	}
	return (0);
}
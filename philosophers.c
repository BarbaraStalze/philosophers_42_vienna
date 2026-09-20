/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 14:48:31 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/18 15:36:03 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_for_all(t_philo_data *p_data);
static int	first_grab(t_philo_data *p_data);
static int	first_grab_wait(t_philo_data *p_data, bool last);
static void	lonely_fucker(t_philo_data *p_data);

void	*philosopher(void *arg)
{
	t_philo_data	*p_data;

	p_data = (t_philo_data *)arg;
	if (p_data->data->n_philosophers == 1)
		return (lonely_fucker(p_data), NULL);
	if (wait_for_all(p_data))
		return (NULL);
	if (first_grab(p_data))
		return (NULL);
	while (42)
	{
		if (eating(p_data))
			return (NULL);
		if (sleeping(p_data))
			return (NULL);
		if (thinking(p_data))
			return (NULL);
	}
	return (NULL);
}

static void	lonely_fucker(t_philo_data *p_data)
{
	pthread_mutex_lock(&p_data->data->start_o_end);
	p_data->data->sim_start = get_time();
	p_data->start_of_last_meal = p_data->data->sim_start;
	p_data->data->alive++;
	pthread_mutex_unlock(&p_data->data->start_o_end);
	pthread_mutex_lock(&p_data->chopstick);
	print_msg(CHOPSTICK, p_data);
	pthread_mutex_unlock(&p_data->chopstick);
	usleep((p_data->data->time_to_die + 100) * 1000);
}

static int	wait_for_all(t_philo_data *p_data)
{
	pthread_mutex_lock(&p_data->data->start_o_end);
	p_data->data->alive++;
	if (p_data->data->alive == p_data->data->n_philosophers)
		p_data->data->sim_start = get_time();
	pthread_mutex_unlock(&p_data->data->start_o_end);
	while (42)
	{
		pthread_mutex_lock(&p_data->data->start_o_end);
		if (p_data->data->simulation_end == true)
		{
			pthread_mutex_unlock(&p_data->data->start_o_end);
			return (1);
		}
		if (p_data->data->alive == p_data->data->n_philosophers)
		{
			pthread_mutex_unlock(&p_data->data->start_o_end);
			break ;
		}
		pthread_mutex_unlock(&p_data->data->start_o_end);
		if (check_for_end(p_data))
			return (1);
		usleep(100);
	}
	p_data->start_of_last_meal = p_data->data->sim_start;
	return (0);
}

static int	first_grab(t_philo_data *p_data)
{
	if (even_philos(p_data))
	{
		if (grab_chopsticks_even(p_data))
			return (1);
	}
	else
	{
		if (first_grab_wait(p_data, false))
			return (1);
		if (grab_chopsticks_uneven(p_data))
			return (1);
	}
	return (0);
}

// Even philosophers start by grabbing the left fork first and then the right,
// uneven philos grab the right fork first after sleeping almost the amount of
// time of time_to_eat.

static int	first_grab_wait(t_philo_data *p_data, bool last)
{
	int64_t	remaining_time;

	(void)last;
	remaining_time = p_data->data->time_to_eat / 2;
	while (remaining_time > 1)
	{
		if (check_for_end(p_data))
			return (1);
		flexsleep(remaining_time, p_data->data->sim_start);
		remaining_time = p_data->data->sim_start + p_data->data->time_to_eat
			- get_time();
	}
	return (0);
}

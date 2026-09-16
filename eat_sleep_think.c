/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 10:35:50 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/16 15:49:16 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allert_waiting(t_philo_data *p_data, int64_t phase_length,
				int64_t phase_start);
static int	try_to_pick_up_chopsticks(t_philo_data *p_data);

int	eating(t_philo_data *p_data)
{
	pthread_mutex_lock(&p_data->data->start_o_end);
	p_data->start_of_last_meal = get_time();
	pthread_mutex_unlock(&p_data->data->start_o_end);
	if (print_msg(EATING, p_data))
		return (drop_chopsticks(p_data), 1);
	if (allert_waiting(p_data, p_data->data->time_to_eat,
			p_data->start_of_last_meal))
		return (drop_chopsticks(p_data), 1);
	drop_chopsticks(p_data);
	p_data->times_eaten++;
	if (p_data->data->minimum_meals
		&& p_data->times_eaten == p_data->data->minimum_meals)
	{
		pthread_mutex_lock(&p_data->data->start_o_end);
		p_data->data->philos_ate_enough++;
		pthread_mutex_unlock(&p_data->data->start_o_end);
	}
	return (0);
}

int	sleeping(t_philo_data *p_data)
{
	int64_t	start_of_sleep;

	start_of_sleep = get_time();
	if (print_msg(SLEEPING, p_data))
		return (1);
	if (allert_waiting(p_data, p_data->data->time_to_sleep, start_of_sleep))
		return (1);
	return (0);
}

int	calc_think_time(t_general_data *data, t_philo_data *p_data, int64_t	remaining)
{
	//int64_t	elapsed;
	int64_t	think_time;

	(void)p_data;
	// elapsed = get_time() - p_data->start_of_last_meal;
	// remaining = data->time_to_die - elapsed;
	think_time = data->time_to_eat - data->time_to_sleep;
	if (think_time <= 0)
		return (100);
	return (((think_time + remaining) / 2) * 1000 + 100);
}

int	thinking(t_philo_data *p_data)
{
	int64_t	start_of_thinking;
	int64_t	time_left;
	int64_t	chill_time;

	start_of_thinking = get_time();
	if (print_msg(THINKING, p_data))
		return (1);
	time_left = p_data->data->time_to_die - (get_time() - p_data->start_of_last_meal);
	chill_time = time_left;
	if (time_left > 0)
	{
		usleep(calc_think_time(p_data->data, p_data, time_left));
	}
	if (try_to_pick_up_chopsticks(p_data))
		return (1);
	return (0);
}

static int	try_to_pick_up_chopsticks(t_philo_data *p_data)
{
	if (p_data->id % 2 == 0)
	{
		if (grab_chopsticks_even(p_data))
			return (1);
	}
	else
	{
		if (grab_chopsticks_uneven(p_data))
			return (1);
	}
	return (0);
}

static int	allert_waiting(t_philo_data *p_data, int64_t phase_length,
				int64_t phase_start)
{
	int64_t	remaining_time;

	remaining_time = phase_length;
	while (remaining_time > 0)
	{
		if (check_for_end(p_data))
			return (1);
		flexsleep(phase_length, phase_start);
		remaining_time = phase_start + phase_length - get_time();
	}
	return (0);
}

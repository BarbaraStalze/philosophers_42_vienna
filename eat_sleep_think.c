/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 10:35:50 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/14 18:44:59 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allert_waiting(t_philo_data *p_data, int64_t phase_length,
				int64_t phase_start);

int	eating(t_philo_data *p_data)
{
	if (check_for_end(p_data))
		return (1);
	if (check_for_death(p_data))
		return (1);
	p_data->start_of_last_meal = get_time();
	print_msg(EATING, p_data, false);
	if (allert_waiting(p_data, p_data->data->time_to_eat,
			p_data->start_of_last_meal))
		return (1);
	p_data->times_eaten++;
	if (p_data->data->minimum_meals
		&& p_data->times_eaten == p_data->data->minimum_meals)
	{
		pthread_mutex_lock(p_data->ate_enough);
		p_data->data->philos_ate_enough++;
		pthread_mutex_unlock(p_data->ate_enough);
	}
	return (0);
}

int	sleeping(t_philo_data *p_data)
{
	int64_t	start_of_sleep;

	if (check_for_end(p_data))
		return (1);
	if (check_for_death(p_data))
		return (1);
	start_of_sleep = get_time();
	print_msg(SLEEPING, p_data, false);
	if (allert_waiting(p_data, p_data->data->time_to_sleep, start_of_sleep))
		return (1);
	return (0);
}

int	thinking(t_philo_data *p_data)
{
	int64_t	start_of_thinking;
	int64_t	time_left;
	int64_t	chill_time;

	if (check_for_end(p_data))
		return (1);
	if (check_for_death(p_data))
		return (1);
	start_of_thinking = get_time();
	time_left = p_data->data->time_to_die - p_data->data->time_to_eat
		- p_data->data->time_to_sleep;
	print_msg(THINKING, p_data, false);
	chill_time = time_left - 5;
	if (chill_time > 0)
	{
		if (allert_waiting(p_data, time_left, start_of_thinking))
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
		if (check_for_death(p_data))
			return (1);
		flexsleep(phase_length, phase_start);
		remaining_time = phase_start + phase_length - get_time();
	}
	return (0);
}

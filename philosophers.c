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
	first_meal();
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

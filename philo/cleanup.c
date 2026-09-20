/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 12:40:09 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/18 12:53:03 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_general_data *data, t_philo_data *p_data)
{
	int	i;

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

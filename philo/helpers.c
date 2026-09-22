/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:15:16 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/22 13:52:43 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_and_initialize(void **data, size_t size)
{
	*data = malloc(size);
	if (!*data)
		return (printf("Error: Malloc failed\n"), 1);
	memset(*data, 0, size);
	return (0);
}

int64_t	get_time(void)
{
	struct timeval		t;
	int64_t				time_in_millis;

	gettimeofday(&t, NULL);
	time_in_millis = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time_in_millis);
}

int	check_for_end(t_philo_data *p_data)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&p_data->data->theone);
	if (p_data->data->simulation_end == true)
		check = 1;
	pthread_mutex_unlock(&p_data->data->theone);
	return (check);
}

int64_t	time_since_start(t_philo_data *p_data)
{
	return (get_time() - p_data->data->sim_start);
}

int	print_msg(char *msg, t_philo_data *p_data)
{
	pthread_mutex_lock(&p_data->data->theone);
	if (p_data->data->simulation_end == true)
		return (pthread_mutex_unlock(&p_data->data->theone), 1);
	printf("%ld %d %s\n", time_since_start(p_data), p_data->id, msg);
	pthread_mutex_unlock(&p_data->data->theone);
	return (0);
}

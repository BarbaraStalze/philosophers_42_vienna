/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:15:16 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 16:19:02 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	malloc_and_initialize(void **data, size_t size)
{
	*data = malloc(size);
	if (!*data)
		return (printf("Error: Malloc failed"), 1);
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
	pthread_mutex_lock(p_data->end);
	if (p_data->data->simulation_end == true)
		check = 1;
	pthread_mutex_unlock(p_data->end);
	return (check);
}

int64_t	time_since_start(t_philo_data *p_data)
{
	int64_t	now;
	
	now = get_time();
	return (now - p_data->data->sim_start);
}

void	print_msg(char *msg, t_philo_data *p_data)
{
	static bool someone_died;
	int64_t		timestamp;
	
	timestamp = times_since_start();
	if (someone_died == false)
	{
		pthread_mutex_lock(p_data->print);
		printf("%d %d %s\n", time, p_data->id, msg);
		if (msg == DEATH)
			someone_died = true;
	}
	pthread_mutex_unlock(p_data->print);
}
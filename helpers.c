/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:15:16 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/16 11:05:36 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&p_data->data->start_o_end);
	if (p_data->data->simulation_end == true)
		check = 1;
	pthread_mutex_unlock(&p_data->data->start_o_end);
	return (check);
}

int64_t	time_since_start(t_philo_data *p_data)
{
	return (get_time() - p_data->data->sim_start);
}

int	print_msg(char *msg, t_philo_data *p_data)
{
	usleep(100);
	pthread_mutex_lock(&p_data->data->start_o_end);
	if (p_data->data->simulation_end == true)
		return (pthread_mutex_unlock(&p_data->data->start_o_end), 1);
	printf("%ld %d %s\n", time_since_start(p_data), p_data->id, msg);
	pthread_mutex_unlock(&p_data->data->start_o_end);
	return (0);
}

int	grab_chopstick(pthread_mutex_t *chopstick, t_philo_data *p_data)
{
	pthread_mutex_lock(chopstick);
	if (print_msg(CHOPSTICK, p_data))
		return (pthread_mutex_unlock(chopstick), 1);
	return (0);
}

int	grab_chopsticks_even(t_philo_data *p_data)
{
	if (grab_chopstick(&p_data->chopstick, p_data))
		return (1);
	if (grab_chopstick(p_data->right_chopstick, p_data))
		return (pthread_mutex_unlock(&p_data->chopstick), 1);
	return (0);
}

int	grab_chopsticks_uneven(t_philo_data *p_data)
{
	if (grab_chopstick(p_data->right_chopstick, p_data))
		return (1);
	if (grab_chopstick(&p_data->chopstick, p_data))
		return (pthread_mutex_unlock(p_data->right_chopstick), 1);
	return (0);
}

void	drop_chopsticks(t_philo_data *p_data)
{
	pthread_mutex_unlock(&p_data->chopstick);
	pthread_mutex_unlock(p_data->right_chopstick);
}

// int	check_for_death(t_philo_data *p_data, t_general_data *data)
// {
// 	if (p_data->start_of_last_meal + p_data->data->time_to_die <= get_time())
// 	{
// 		print_msg(DEATH, p_data, true);
// 		pthread_mutex_lock(p_data->died);
// 		p_data->data->someone_died = true;
// 		pthread_mutex_unlock(p_data->died);
// 		return (1);
// 	}
// 	return (0);
// }

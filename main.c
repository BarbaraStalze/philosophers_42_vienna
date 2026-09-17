/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:48:17 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/17 13:44:32 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor(t_general_data *data, t_philo_data *p_data);

int	main(int ac, char **av)
{
	t_general_data		data;
	//t_mutex_thread_data	mt_data;
	t_philo_data		*p_data;

	if (ac == 5 || ac == 6)
	{
		if (initiate_general_data(av, &data))
			return (1);
		if (initiate_mutexes(&data))
			return (1);
		if (initiate_philosophers(&data, &p_data))
			return (free(p_data), 1);
		monitor(&data, p_data);
		join_threads(p_data, data.n_philosophers);
		cleanup(&data, p_data);
		return (0);
	}
	else
	{
		printf("Error: Incorrect amount of arguments");
		return (1);
	}
}

static void	monitor(t_general_data *data, t_philo_data *p_data)
{
	int	i;

	while (42)
	{
		pthread_mutex_lock(&data->start_o_end);
		if (data->alive == data->n_philosophers)
		{
			pthread_mutex_unlock(&data->start_o_end);
			break ;
		}
		pthread_mutex_unlock(&data->start_o_end);
		usleep(200);
	}
	usleep(500);
	while (42)
	{
		i = 0;
		while (i < data->n_philosophers)
		{
			pthread_mutex_lock(&data->start_o_end);
			if (p_data[i].start_of_last_meal + p_data[i].data->time_to_die <= get_time())
			{
				printf("%ld %d %s\n", time_since_start(&p_data[i]), i + 1, DEATH);
				//printf("%ld %ld\n", p_data[i].start_of_last_meal, get_time());
				data->simulation_end = true;
			}
			else if (data->minimum_meals)
			{
				if (data->philos_ate_enough == data->n_philosophers)
					data->simulation_end = true;	
			}
			if (data->simulation_end == true)
				return ((void)pthread_mutex_unlock(&data->start_o_end));
			pthread_mutex_unlock(&data->start_o_end);
			i++;
		}
		usleep(50);
	}
}

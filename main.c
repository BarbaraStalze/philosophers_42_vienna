/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:48:17 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/14 18:44:59 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor(t_general_data *data, t_mutex_thread_data *mt_data);

int	main(int ac, char **av)
{
	t_general_data		data;
	t_mutex_thread_data	mt_data;
	t_philo_data		*p_data;

	p_data = NULL;
	if (ac == 5 || ac == 6)
	{
		if (initiate_general_data(av, &data))
			return (1);
		if (initiate_mutexes(&mt_data, &data))
			return (cleanup(&mt_data, &data, p_data), 1);
		if (initiate_philosophers(&mt_data, &data, p_data))
			return (cleanup(&mt_data, &data, p_data), 1);
		monitor(&data, &mt_data);
		join_threads(&mt_data, &data);
		cleanup(&mt_data, &data, p_data);
		return (0);
	}
	else
	{
		printf("Error: Incorrect amount of arguments");
		return (1);
	}
}

static void	monitor(t_general_data *data, t_mutex_thread_data *mt_data)
{
	bool	sim_end;

	sim_end = false;
	while (42)
	{
		if (data->minimum_meals)
		{
			pthread_mutex_lock(&mt_data->ate_enough);
			if (data->philos_ate_enough == data->minimum_meals)
				sim_end = true;
			pthread_mutex_unlock(&mt_data->ate_enough);
		}
		if (sim_end == false)
		{
			pthread_mutex_lock(&mt_data->died);
			if (data->someone_died == true)
				sim_end = true;
			pthread_mutex_unlock(&mt_data->died);
		}
		if (sim_end == true)
		{
			pthread_mutex_lock(&mt_data->end);
			data->simulation_end = true;
			pthread_mutex_unlock(&mt_data->end);
			return ;
		}
	}
}

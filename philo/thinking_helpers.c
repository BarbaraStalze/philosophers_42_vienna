/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:30:02 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/18 15:31:35 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	calc_think_time(t_general_data *data, t_philo_data *p_data,
		int64_t	remaining)
{
	int64_t	think_time;

	(void)p_data;
	think_time = data->time_to_eat - data->time_to_sleep;
	if (think_time < 0)
		return (100);
	return (((think_time + remaining) / 2) * 1000 + 100);
}

int	try_to_pick_up_chopsticks(t_philo_data *p_data)
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

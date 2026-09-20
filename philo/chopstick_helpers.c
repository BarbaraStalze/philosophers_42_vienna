/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chopstick_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:57:41 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/20 11:48:22 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

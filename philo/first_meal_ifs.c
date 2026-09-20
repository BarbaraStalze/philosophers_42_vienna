/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_meal_ifs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 17:46:47 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/14 18:44:59 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_philos(t_philo_data *p_data)
{
	if (p_data->id % 2 == 0)
		return (1);
	return (0);
}

int	uneven_philos_without_last(t_philo_data *p_data)
{
	if ((p_data->data->n_philosophers % 2 == 0 && p_data->id % 2 == 1)
		|| (p_data->data->n_philosophers % 2 == 1
			&& p_data->id % 2 == 1
			&& p_data->id != p_data->data->n_philosophers))
		return (1);
	return (0);
}

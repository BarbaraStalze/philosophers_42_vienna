/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mutexes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 12:10:30 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/21 17:17:39 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initiate_mutex(t_general_data *data)
{
	if (pthread_mutex_init(&data->theone, NULL))
		return (1);
	return (0);
}

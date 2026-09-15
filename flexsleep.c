/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexsleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 17:02:24 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 17:43:21 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	flexsleep(int64_t max_phase_length, int64_t start_of_phase)
{
	int64_t	curr_time;
	int64_t	end_of_phase;
	int64_t	remaining_time;

	curr_time = get_time();
	end_of_phase = start_of_phase + max_phase_length;
	remaining_time = end_of_phase - curr_time;
	if (remaining_time > 500)
		usleep(400000);
	else if (remaining_time > 50)
		usleep(remaining_time * 1000 - 5000);
	else
		usleep(100);
}

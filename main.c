/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:48:17 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 12:50:02 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_general_data		data;
	t_mutex_thread_data	mt_data;
	
	if (ac == 5 || ac == 6)
	{
		if (initiate_general_data(av, &data))
			return (1);
		if (initiate_mutexes(&mt_data, &data))
			return (cleanup(&mt_data, &data), 1);
	//	if (initiate_philosophers(av))
	//		return (1);
		return (0);
	}
	else
	{
		printf("Error: Incorrect amount of arguments");
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_general_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 11:53:10 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 12:02:50 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	add_args(char **av, t_general_data *data);
static int	ft_isdigit(int c);
static int	char_to_int(const char *nptr);

int	initiate_general_data(char **av, t_general_data *data)
{
	int	i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (printf("Argument is not a number"), 1);
			j++;
		}
		i++;
	}
	if (add_args(av, data))
		return (1);
	return (0);
}

static int	add_args(char **av, t_general_data *data)
{
	data->n_philosophers = char_to_int(av[1]);
	if (data->n_philosophers == -1)
		return (1);
	data->time_to_die = char_to_int(av[2]);
	if (data->time_to_die == -1)
		return (1);
	data->time_to_eat = char_to_int(av[3]);
	if (data->time_to_eat == -1)
		return (1);
	data->time_to_sleep = char_to_int(av[4]);
	if (data->time_to_sleep == -1)
		return (1);
	if (av[5])
	{
		data->minimum_meals = char_to_int(av[5]);
		if (data->minimum_meals == 0 || data->minimum_meals == -1)
			return (1);
	}
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	char_to_int(const char *nptr)
{
	int		i;
	long	rtrn;

	i = 0;
	rtrn = 0;
	while (nptr[i])
	{
		rtrn = rtrn * 10 + (nptr[i] - 48);
		if (rtrn > INT_MAX)
			return (printf("Argument is bigger than INT_MAX"), -1);
		i++;
	}
	return ((int)rtrn);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_general_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 11:53:10 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/22 14:55:56 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	add_args(char **av, t_general_data *data);
static int	ft_isdigit(int c);
static int	char_to_int(const char *nptr);

int	initiate_general_data(char **av, t_general_data *data)
{
	int	i;
	int	j;

	i = 1;
	memset(data, 0, sizeof(t_general_data));
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (printf("Error: Argument is not a \
					positive number\n"), 1);
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
	if (data->n_philosophers == -1 || data->n_philosophers == 0)
		return (1);
	if (data->n_philosophers > 200)
		return (printf("Error: You shall not test with more \
			than 200 philos\n"), 1);
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
			return (printf("Error: Argument is bigger than INT_MAX\n"), -1);
		i++;
	}
	return ((int)rtrn);
}

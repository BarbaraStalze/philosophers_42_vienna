/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:15:16 by bastalze          #+#    #+#             */
/*   Updated: 2026/09/13 13:19:12 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	malloc_and_initialize(void **data, size_t size)
{
	*data = malloc(size);
	if (!*data)
		return (printf("Error: Malloc failed"), 1);
	memset(*data, 0, size);
	return (0);
}


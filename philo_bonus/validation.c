/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:58:47 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 15:59:31 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	validation_args(int argc, char **argv)
{
	int		i;
	long	n;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (0);
		n = ft_atoi(argv[i]);
		if (i == 1)
		{
			if (n <= 0 || n > 200)
				return (0);
		}
		else
		{
			if (n <= 0 || n > 2147483647)
				return (0);
		}
		i++;
	}
	return (1);
}

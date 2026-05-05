/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:52:22 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 13:59:30 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	clean_func(t_info *info)
{
	if (info->philos)
		free(info->philos);
	if (info->forks)
		free(info->forks);
	return (0);
}

int	first_initial(char **argv, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	info->num = ft_atoi(argv[1]);
	info->philos = malloc((info->num) * sizeof(t_philo));
	info->forks = malloc((info->num) * sizeof(pthread_mutex_t));
	if (!info->forks || !info->philos)
		return (clean_func(info));
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		info->flag_must_eat = 1;
		info->times_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		info->flag_must_eat = 0;
		info->times_must_eat = 0;
	}
	info->start_time = get_times_in_ms();
	info->stop = 0;
	if (pthread_mutex_init(&info->stop_flag, NULL) != 0)
		return (clean_func(info));
	if (pthread_mutex_init(&info->print, NULL) != 0)
	{
		pthread_mutex_destroy(&info->stop_flag);
		return (clean_func(info));
	}
	return (1);
}



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
	free(info->philos);
	free(info->forks);
	return (0);
}

int	first_initial(char **argv, t_info *info)
{
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
	pthread_mutex_init(&info->stop_flag, NULL);
	pthread_mutex_init(&info->print, NULL);
	return (1);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		info->philos[i].id = i + 1;
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].right_fork = &info->forks[(i + 1) % info->num];
		info->philos[i].last_meal_time = info->start_time;
		info->philos[i].num_meals = 0;
		info->philos[i].info = info;
		if (pthread_mutex_init(&info->philos[i].meals, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&info->philos[i].last_time, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	create_threads(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->num)
	{
		if (pthread_create(&info->philos[index].thread, NULL,
				&routine, &info->philos[index]) != 0)
			return (0);
		index++;
	}
	return (1);
}

int	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

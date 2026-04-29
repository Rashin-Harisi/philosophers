/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:08:41 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 15:12:04 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		if (pthread_mutex_destroy(&info->forks[i]) != 0
			|| pthread_mutex_destroy(&info->philos[i].last_time) != 0
			|| pthread_mutex_destroy(&info->philos[i].meals) != 0)
			return (0);
		i++;
	}
	return (1);
}

long	get_last_meal_time(t_philo *philo)
{
	long	last;

	pthread_mutex_lock(&philo->last_time);
	last = philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_time);
	return (last);
}

int	get_nums_meal(t_philo *philo)
{
	int	nums;

	pthread_mutex_lock(&philo->meals);
	nums = philo->num_meals;
	pthread_mutex_unlock(&philo->meals);
	return (nums);
}

int	get_stop_flag(t_info *info)
{
	int	flag;

	pthread_mutex_lock(&info->stop_flag);
	flag = info->stop;
	pthread_mutex_unlock(&info->stop_flag);
	return (flag);
}

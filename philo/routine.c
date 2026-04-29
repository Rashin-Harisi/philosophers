/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:18:26 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 15:32:06 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print(t_philo *philo, char *text)
{
	long	now;

	pthread_mutex_lock(&philo->info->print);
	if (!get_stop_flag(philo->info) || ft_strcmp(text, "died") == 0)
	{
		now = get_times_in_ms();
		printf ("%ld %d %s\n", (now - philo->info->start_time),
			philo->id, text);
	}
	pthread_mutex_unlock(&philo->info->print);
}

void	eat(t_philo *philo)
{
	if (philo->id == philo->info->num)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->last_time);
	philo->last_meal_time = get_times_in_ms();
	pthread_mutex_unlock(&philo->last_time);
	print(philo, "is eating");
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meals);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->meals);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{
	print(philo, "is sleeping");
	usleep(philo->info->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print(philo, "is thinking");
	if (philo->info->num % 2 != 0)
		usleep((philo->info->time_to_eat / 2) * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->num == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		if (!get_stop_flag(philo->info))
			usleep(1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_stop_flag(philo->info))
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

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

void	eat(t_philo *philo)
{
	sem_wait(philo->info->taken_forks);
	sem_wait(philo->info->forks);
	print(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print(philo, "has taken a fork");
	sem_post(philo->info->taken_forks);
	sem_wait(philo->last_meal);
	philo->last_meal_time = get_times_in_ms();
	sem_post(philo->last_meal);
	print(philo, "is eating");
	usleep(philo->info->time_to_eat * 1000);
	sem_wait(philo->meals);
	philo->num_meals++;
	sem_post(philo->meals);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
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

void	routine(t_philo *philo)
{
	if (philo->info->num == 1)
	{
		sem_wait(philo->info->forks);
		print(philo, "has taken a fork");
		while (1)
			usleep(1000);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
}

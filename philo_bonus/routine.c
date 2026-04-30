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

	sem_wait(philo->info->print);
	if (!get_stop_flag(philo->info) || ft_strcmp(text, "died") == 0)
	{
		now = get_times_in_ms();
		printf ("%ld %d %s\n", (now - philo->info->start_time),
			philo->id, text);
	}
	sem_post(philo->info->print);
}

void	eat(t_philo *philo)
{

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
		sem_wait(philo->info->forks);
		print(philo, "has taken a fork");
		if (!get_stop_flag(philo->info))
			usleep(1000);
		sem_post(philo->info->forks);
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

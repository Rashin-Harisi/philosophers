/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:12:26 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 15:17:57 by rabdolho         ###   ########.fr       */
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

int	get_nums_meal(t_philo *philo)
{
	int	num;

	sem_wait(philo->meals);
	num = philo->num_meals;
	sem_post(philo->meals);
	return (num);
}

long	get_last_meal_time(t_philo *philo)
{
	long time;

	sem_wait(philo->last_meal);
	time = philo->last_meal_time;
	sem_post(philo->last_meal);
	return (time);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		
		if (get_times_in_ms() - get_last_meal_time(philo)
			> philo->info->time_to_die)
		{
			print(philo , "died");
			exit(1);
		}
		if (philo->info->flag_must_eat && get_nums_meal(philo) >= philo->info->times_must_eat)
			exit(0);
		usleep(1000);
	}
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || !validation_args(argc, argv))
		return (1);
	if (!first_initial(argv, &info))
		return (1);
	if (!init_philo(&info))
		return (cleanup(&info));
	if (!create_processes(&info))
		return (cleanup(&info));
	
	free(info.philos);
	free(info.forks);
	return (0);
}

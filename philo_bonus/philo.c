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

void	*monitor(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo->info->num)
		{
			if (get_times_in_ms() - philo->last_meal_time
				> philo->info->time_to_die)
			{
				print(&philo->info->philos[i], "died");
				exit(1);
			}
			i++;
		}
		if (philo->info->flag_must_eat && all_eat_enough(philo->info))
			exit(1);
		usleep(1000);
	}
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

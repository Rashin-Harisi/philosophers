#include "philo.h"



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
		{
			cleanup_mutexes_in_philo(info, i);
			return (0);
		}
		if (pthread_mutex_init(&info->philos[i].last_time, NULL) != 0)
		{
			pthread_mutex_destroy(&info->philos[i].meals);
			cleanup_mutexes_in_philo(info, i);
			return (0);
		}
		i++;
	}
	return (1);
}
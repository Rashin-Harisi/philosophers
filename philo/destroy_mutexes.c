#include "philo.h"


void	destroy_mutexes_end(t_info *info)
{
    int	i;
    
	i = 0;
	while (i < info->num)
	{
		pthread_mutex_destroy(&info->forks[i]);
        pthread_mutex_destroy(&info->philos[i].last_time);
        pthread_mutex_destroy(&info->philos[i].meals);
		i++;
	}
	pthread_mutex_destroy(&info->stop_flag);
	pthread_mutex_destroy(&info->print);
}

void	destroy_mutexes_forks(t_info *info, int index)
{
    int	i;

    i = 0;
    while (i < index)
    {
        pthread_mutex_destroy(&info->forks[i]);
        i++;
    }
}

void	cleanup_mutexes_in_philo(t_info *info, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&info->philos[i].meals);
		pthread_mutex_destroy(&info->philos[i].last_time);
		i++;
	}
}

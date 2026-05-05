#include "philo.h"

void	cleanup_threads(t_info *info, int index)
{
	int	i;

	i = 0;
	set_stop(info);
	while (i < index)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
}

int	create_threads(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->num)
	{
		if (pthread_create(&info->philos[index].thread, NULL,
				&routine, &info->philos[index]) != 0)
			{
				cleanup_threads(info, index);
				return (0);
			}
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

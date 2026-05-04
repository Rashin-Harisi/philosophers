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
	now = get_times_in_ms();
	printf ("%ld %d %s\n", (now - philo->info->start_time),
			philo->id, text);
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

void	cleanup(t_info *info)
{
	int		i;
	char	*name;

	i = 0;
	while (i < info->num)
	{
		if (info->philos[i].last_meal && info->philos[i].last_meal != SEM_FAILED)
			sem_close(info->philos[i].last_meal);
		if (info->philos[i].meals && info->philos[i].meals != SEM_FAILED)
			sem_close(info->philos[i].meals);
		name = create_name(&info->philos[i], "/last_meal");
		if (name)
		{
			sem_unlink(name);
			free(name);
		}
		name = create_name(&info->philos[i], "/meals");
		if (name)
		{
			sem_unlink(name);
			free(name);
		}
		i++;
	}
	if (info->forks && info->forks != SEM_FAILED)
		sem_close(info->forks);
	if (info->print && info->print != SEM_FAILED)
		sem_close(info->print);
	if (info->stop_flag && info->stop_flag != SEM_FAILED)
		sem_close(info->stop_flag);
	if (info->taken_forks && info->taken_forks != SEM_FAILED)
		sem_close(info->taken_forks);
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/forks");
	sem_unlink("/taken_forks");
	free(info->philos);
	free(info->pids);
}

void	wait_processes(t_info *info)
{
	int		status;
	int		i;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		kill_childs(info, info->num);
	i = 0;
	while (i < info->num -1 )
	{
		waitpid(-1, NULL, 0); // it waits for remaianed child
		i++;
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
		return (cleanup(&info), 1);
	if (!create_processes(&info))
		return (cleanup(&info), 1);
	wait_processes(&info);
	cleanup(&info);
	return (0);
}

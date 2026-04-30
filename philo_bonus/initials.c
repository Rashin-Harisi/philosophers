/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:52:22 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 13:59:30 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	clean_func(t_info *info)
{
	if (info->forks && info->forks != SEM_FAILED)
		sem_close(info->forks);
	if (info->print && info->print != SEM_FAILED)
		sem_close(info->print);
	if (info->stop_flag && info->stop_flag != SEM_FAILED)
		sem_close(info->stop_flag);
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/forks");
	free(info->philos);
	free(info->pids);
	return (0);
}

int	first_initial(char **argv, t_info *info)
{
	info->philos = NULL;
	info->pids = NULL;
	info->forks = NULL;
	info->print = NULL;
	info->stop_flag = NULL;
	info->num = ft_atoi(argv[1]);
	info->philos = malloc((info->num) * sizeof(t_philo));
	info->pids = malloc((info->num) * sizeof(pid_t));
	if (!info->pids || !info->philos)
		return (clean_func(info));
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		info->flag_must_eat = 1;
		info->times_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		info->flag_must_eat = 0;
		info->times_must_eat = 0;
	}
	info->start_time = get_times_in_ms();
	sem_unlink("/print");
	info->print = sem_open("/print", O_CREAT, 0644, 1);
	sem_unlink("/stop");
	info->stop_flag = sem_open("/stop", O_CREAT, 0644, 1);
	sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT, 0644, info->num);
	if (info->forks == SEM_FAILED
		|| info->print == SEM_FAILED
		|| info->stop_flag == SEM_FAILED)
		return (clean_func(info));
	return (1);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		info->philos[i].id = i + 1;
		info->philos[i].last_meal_time = info->start_time;
		info->philos[i].num_meals = 0;
		info->philos[i].info = info;
		i++;
	}
	return (1);
}

int	create_processes(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->num)
	{
		info->pids[index] = fork();
		if (info->pids[index] < 0)
		{
			kill_childs(info, index);
			waitpid_childs(info, index);
			return (0);
		}
		else if (info->pids[index] == 0)
		{
			if (pthread_create(&info->philos[index].monitor, NULL, monitor, &info->philos[index]) != 0)
				exit(1);
			pthread_detach(info->philos[index].monitor);
			routine(&info->philos[index]);
			exit(0);
		}
		index++;
	}
	return (1);
}

void kill_childs(t_info *info, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		kill(info->pids[i], SIGKILL);
		i++;
	}
}

void waitpid_childs(t_info *info, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		waitpid(info->pids[i], NULL, 0);
		i++;
	}
}
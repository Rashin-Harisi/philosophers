/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:37:48 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 15:44:18 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				num_meals;
	sem_t			*last_meal;
	sem_t			*meals;
	pthread_t		monitor;
	t_info			*info;
}	t_philo;

typedef struct s_info
{
	int				num;
	pid_t			*pids;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*stop_flag;
	sem_t			*taken_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				flag_must_eat;
	int				times_must_eat;
	long			start_time;
}	t_info;

long	ft_atoi(char *str);
int		is_digit(char *str);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*create_name(t_philo *philo, char *main);
int		first_initial(char **argv, t_info *info);
int		create_processes(t_info *info);
void	kill_childs(t_info *info, int index);
void	waitpid_childs(t_info *info, int index);
void	*monitor(void *arg);
void	print(t_philo *philo, char *text);
int		get_nums_meal(t_philo *philo);
long	get_last_meal_time(t_philo *philo);
long	get_times_in_ms(void);

#endif

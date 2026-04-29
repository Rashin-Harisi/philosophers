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

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_time;
	pthread_mutex_t	meals;
	long			last_meal_time;
	int				num_meals;
	t_info			*info;
}	t_philo;

typedef struct s_info
{
	int				num;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				stop;
	pthread_mutex_t	stop_flag;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				flag_must_eat;
	int				times_must_eat;
	long			start_time;
}	t_info;

long	ft_atoi(char *str);
int		is_digit(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		first_initial(char **argv, t_info *info);
int		create_threads(t_info *info);
int		join_threads(t_info *info);
void	*routine(void *arg);
int		init_mutexes(t_info *info);
int		init_philo(t_info *info);
int		destroy_mutexes(t_info *info);
int		cleanup(t_info *info);
long	get_times_in_ms(void);
void	print(t_philo *philo, char *text);
void	eat(t_philo *philo);
long	get_last_meal_time(t_philo *philo);
int		get_nums_meal(t_philo *philo);
int		get_stop_flag(t_info *info);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);
int		validation_args(int argc, char **argv);
void	set_stop(t_info *info);
int		clean_func(t_info *info);

#endif

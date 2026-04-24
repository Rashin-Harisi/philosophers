#ifndef PHILO
#define PHILO

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

typedef struct  s_info
{
    int num;
    pthread_t *philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int flag_must_eat;
    int times_must_eat;
} t_info;

typedef struct s_philo
{

} t_philo;


int	ft_atoi(char *str);
int first_initial(char **argv, t_info *info);
int create_threads(t_info *info);
int join_threads(t_info *info);

#endif
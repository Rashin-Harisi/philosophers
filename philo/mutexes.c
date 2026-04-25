#include "philo.h"

int init_mutexes(t_info *info)
{
    int i = 0;
    while (i < info->num)
    {
        if(pthread_mutex_init(&info->forks[i], NULL) != 0) 
            return 0;
        i++;
    }
    return 1;
}

int destroy_mutexes(t_info *info)
{
    int i = 0;
    while (i < info->num)
    {
        if(pthread_mutex_destroy(&info->forks[i]) != 0) 
            return 0;
        i++;
    }
    return 1;
}
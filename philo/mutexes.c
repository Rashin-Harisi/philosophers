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
        if(pthread_mutex_destroy(&info->forks[i]) != 0
            || pthread_mutex_destroy(&info->philos[i].last_time) != 0
            || pthread_mutex_destroy(&info->philos[i].meals) != 0) 
            return 0;
        i++;
    }
    return 1;
}

long get_last_meal_time(t_philo *philo)
{
    long last;

    pthread_mutex_lock(&philo->last_time);
    last = philo->last_meal_time;
    pthread_mutex_unlock(&philo->last_time);
    return (last);
}

int get_nums_meal(t_philo *philo)
{
    int nums;

    pthread_mutex_lock(&philo->meals);
    nums = philo->num_meals;
    pthread_mutex_unlock(&philo->meals);
    return (nums);
}
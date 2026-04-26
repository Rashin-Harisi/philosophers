#include "philo.h"


void print(t_philo *philo, char *text)
{
    long now;
    pthread_mutex_lock(&philo->info->print);
    if(!get_stop_flag(philo->info) || ft_strcmp(text, "died") == 0)
    {
        now = get_times_in_ms();
        printf("%ld %d %s\n", (now - philo->info->start_time), philo->id, text);
    }
    pthread_mutex_unlock(&philo->info->print);
}


void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print(philo, "has taken a fork.");
    pthread_mutex_lock(philo->right_fork);
    print(philo, "has taken a fork.");
    print(philo, "is eating.");
    pthread_mutex_lock(&philo->last_time);
    philo->last_meal_time = get_times_in_ms();
    pthread_mutex_unlock(&philo->last_time);
    pthread_mutex_lock(&philo->meals);
    philo->num_meals++;
    pthread_mutex_unlock(&philo->meals);
    usleep(philo->info->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);

}
/*
void sleep_philo(t_philo *philo)
{}

void think(t_philo *philo)
{}
*/
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->info->stop)
    {
        eat(philo);
        //sleep_philo(philo);
        //think(philo);
    }
    return NULL;
}


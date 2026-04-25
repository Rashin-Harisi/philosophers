# include "philo.h"

void *sleep_func(void *arg){
    t_philo *philo = (t_philo *)arg;
    printf("philo %d is sleeping\n", philo->id);
    return NULL;
}

int cleanup(t_info *info)
{
    free(info->philos);
    free(info->forks);
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 5 && argc !=6 )  return 1;
    t_info info;
    long now = get_times_in_ms();
    printf(" time : %ld\n", now);
    if(!first_initial(argv, &info)) return 1;
    if(!init_mutexes(&info))
        return (cleanup(&info));
    if(!init_philo(&info))
        return (cleanup(&info));
    if(!join_threads(&info))
        return (cleanup(&info));
    if (!destroy_mutexes(&info))
        return (cleanup(&info));
    free(info.philos);
    free(info.forks);
    return 0;
}
# include "philo.h"

int first_initial(char **argv, t_info *info)
{
    info->num = ft_atoi(argv[1]);
    info->philos = malloc((info->num) * sizeof(pthread_t));
    if(!info->philos) return 0;
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]);
    info->time_to_sleep = ft_atoi(argv[4]);
    if(argv[5])
    {
        info->flag_must_eat = 1;
        info->times_must_eat = ft_atoi(argv[5]);
    }
    else 
    {
        info->flag_must_eat = 0;
        info->times_must_eat = 0;
    }
    return 1;
}

void *sleep_func(void *arg){
    (void)arg;
    printf("sleep\n");
    return NULL;
}

int create_threads(t_info *info)
{
    int i = 0;
    while (i < info->num)
    {
        if(pthread_create(&info->philos[i], NULL, &sleep_func, NULL) != 0)
            return 0;
        i++;
    }
    return 1;
}

int join_threads(t_info *info)
{
    int i = 0;
    while (i < info->num)
    {
        if(pthread_join(info->philos[i], NULL) != 0)
            return 0;
        i++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 5 && argc !=6 )  return 1;
    t_info info;
    if(!first_initial(argv, &info)) return 1;
    if (!create_threads(&info)) return (free(info.philos), 1);

    if(!join_threads(&info)) return (free(info.philos), 1);
    free(info.philos);
    return 0;
}
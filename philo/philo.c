# include "philo.h"

int all_eat_enough(t_info *info)
{
    int count = 0;
    int i = 0;

    while( i < info->num)
    {
        if (get_nums_meal(&info->philos[i]) >= info->times_must_eat)
            count++;
        i++;
    }
    if (count == info->num) return 1;
    else return 0;
}


void monitor(t_info *info)
{
    int i;
    while (1)
    {
        i = 0;
        while ( i < info->num)
        {
            if( get_times_in_ms() - get_last_meal_time(&info->philos[i]) > info->time_to_die)
            {
                pthread_mutex_lock(&info->stop_flag);
                info->stop = 1;
                pthread_mutex_unlock(&info->stop_flag);
                print(&info->philos[i], "died");
                return;
            }
            i++;
        }
        if (info->flag_must_eat && all_eat_enough(info))
        {
            pthread_mutex_lock(&info->stop_flag);
            info->stop = 1;
            pthread_mutex_unlock(&info->stop_flag);
            return;
        }
        usleep(1000);        
    }
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
    //long now = get_times_in_ms();
    //printf(" time : %ld\n", now);
    if(!first_initial(argv, &info)) return 1;
    if(!init_mutexes(&info))
        return (cleanup(&info));
    if(!init_philo(&info))
        return (cleanup(&info));
    monitor(&info);
    if(!join_threads(&info))
        return (cleanup(&info));
    if (!destroy_mutexes(&info))
        return (cleanup(&info));
    if(pthread_mutex_destroy(&info.print) != 0)
        return (cleanup(&info));
    if(pthread_mutex_destroy(&info.stop_flag) != 0)
        return (cleanup(&info));
    free(info.philos);
    free(info.forks);
    return 0;
}
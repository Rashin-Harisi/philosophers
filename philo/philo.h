#ifndef PHILO
#define PHILO

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

//forward decleration;
typedef struct s_info t_info;
typedef struct s_philo t_philo; 

typedef struct s_philo
{
    int id;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t last_time; //because it is changed in one function and called in another function,
    pthread_mutex_t meals;     //it needs to have mutex to be safe in each process
    long last_meal_time;
    int num_meals;
    t_info *info;
} t_philo;

typedef struct  s_info
{
    int num;
    t_philo *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    int stop;
    pthread_mutex_t stop_flag;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int flag_must_eat;
    int times_must_eat;
    long start_time;
} t_info;

int	ft_atoi(char *str);
int	ft_strcmp(const char *s1, const char *s2);
int first_initial(char **argv, t_info *info);
int create_threads(t_info *info, int index);
int join_threads(t_info *info);
void *routine(void *arg);
int init_mutexes(t_info *info);
int init_philo(t_info *info);
int destroy_mutexes(t_info *info);
int cleanup(t_info *info);
long get_times_in_ms(void);
void print(t_philo *philo, char *text);
void eat(t_philo *philo);
long get_last_meal_time(t_philo *philo);
int get_nums_meal(t_philo *philo);
int get_stop_flag(t_info *info);
//void sleep_philo(t_philo *philo);
//void think(t_philo *philo);

#endif
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    int             is_dead;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t death;
    struct s_philo  *philos;
} t_data;

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    long long       last_meal;
    int             meals_eaten;
    pthread_t       thread;
    struct s_data   *data;
} t_philo;

// time.c
long long   get_time(void);

// print.c
void        print_status(t_philo *philo, char *status);

// utils.c
int         ft_atoi(const char *str);

// init.c
int         init_data(t_data *data);
int         init_mutexes(t_data *data);
int         init_philosophers(t_data *data);

// check.c
int         check_death(t_philo *philo);
int         check_meals(t_data *data);

// routine.c
void        *philosopher_routine(void *arg);

// parse.c
int         parse_args(t_data *data, int argc, char **argv);

// cleanup.c
void        cleanup(t_data *data);

#endif 
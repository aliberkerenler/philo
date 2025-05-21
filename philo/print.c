#include "philo.h"

void    print_status(t_philo *philo, char *status)
{
    long long   time;

    pthread_mutex_lock(&philo->data->print);
    time = get_time() - philo->data->start_time;
    printf("%lld %d %s\n", time, philo->id, status);
    pthread_mutex_unlock(&philo->data->print);
} 
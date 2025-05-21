#include "philo.h"

void    cleanup(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->death);
    free(data->forks);
    free(data->philos);
} 
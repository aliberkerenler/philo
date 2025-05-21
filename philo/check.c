#include "philo.h"

int check_death(t_philo *philo)
{
    long long current_time;
    
    pthread_mutex_lock(&philo->data->death);
    if (philo->data->is_dead)
    {
        pthread_mutex_unlock(&philo->data->death);
        return (1);
    }
    current_time = get_time();
    if (current_time - philo->last_meal >= philo->data->time_to_die)
    {
        print_status(philo, "died");
        philo->data->is_dead = 1;
        pthread_mutex_unlock(&philo->data->death);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->death);
    return (0);
}

int check_meals(t_data *data)
{
    int i;
    int all_ate;

    i = 0;
    all_ate = 1;
    while (i < data->num_philos)
    {
        if (data->philos[i].meals_eaten < data->must_eat)
        {
            all_ate = 0;
            break;
        }
        i++;
    }
    if (all_ate)
    {
        data->is_dead = 1;
        return (1);
    }
    return (0);
} 
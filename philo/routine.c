#include "philo.h"

static void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        print_status(philo, "has taken a fork");
    }
}

static void eat(t_philo *philo)
{
    print_status(philo, "is eating");
    philo->last_meal = get_time();
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
    philo->meals_eaten++;
}

static void sleep_and_think(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
    print_status(philo, "is thinking");
}

void    *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!check_death(philo))
    {
        take_forks(philo);
        eat(philo);
        if (philo->data->must_eat != -1)
        {
            pthread_mutex_lock(&philo->data->death);
            if (check_meals(philo->data))
            {
                pthread_mutex_unlock(&philo->data->death);
                return (NULL);
            }
            pthread_mutex_unlock(&philo->data->death);
        }
        sleep_and_think(philo);
    }
    return (NULL);
} 
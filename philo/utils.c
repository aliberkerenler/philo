#include "philo.h"

long long   get_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    print_status(t_philo *philo, char *status)
{
    long long   time;

    pthread_mutex_lock(&philo->data->print);
    time = get_time() - philo->data->start_time;
    printf("%lld %d %s\n", time, philo->id, status);
    pthread_mutex_unlock(&philo->data->print);
}

int ft_atoi(const char *str)
{
    int i;
    int sign;
    int result;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
} 
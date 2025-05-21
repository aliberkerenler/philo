#include "philo.h"

int parse_args(t_data *data, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        return (1);
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat = -1;
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    if (data->num_philos < 1 || data->time_to_die < 0 || 
        data->time_to_eat < 0 || data->time_to_sleep < 0 || 
        (argc == 6 && data->must_eat < 0))
        return (1);
    return (0);
} 
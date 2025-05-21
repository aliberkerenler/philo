#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;

    if (parse_args(&data, argc, argv))
    {
        printf("Error: Invalid arguments\n");
        return (1);
    }
    if (init_data(&data))
    {
        printf("Error: Initialization failed\n");
        return (1);
    }
    cleanup(&data);
    return (0);
} 
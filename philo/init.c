/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:58:47 by aerenler          #+#    #+#             */
/*   Updated: 2025/07/01 16:58:47 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->death, NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal = get_time();
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_time_lock, NULL))
			return (1);
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->is_dead = 0;
	data->start_time = get_time();
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	if (init_mutexes(data))
		return (1);
	if (init_philosophers(data))
		return (1);
	return (0);
}

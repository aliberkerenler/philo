/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:24:47 by aerenler          #+#    #+#             */
/*   Updated: 2025/08/18 18:01:31 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		eat_sleep_routine(philo);
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		think_routine(philo, 0);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (philo->data->must_eat == 0)
		return (NULL);
	if (philo->data->num_philos == 1)
		return (lone_philo_routine(philo));
	if (philo->id % 2 == 0)
		think_routine(philo, 1);
	philo_loop(philo);
	return (NULL);
}

static void	monitor_loop(t_data *d, int *full_count, int *someone_died,
		long long now)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_mutex_lock(&d->philos[i].meal_time_lock);
		now = get_time();
		if (!d->is_dead && (now - d->philos[i].last_meal >= d->time_to_die))
		{
			pthread_mutex_lock(&d->death);
			if (!d->is_dead)
			{
				d->is_dead = 1;
				pthread_mutex_lock(&d->print);
				printf("%lld %d died\n", now - d->start_time, d->philos[i].id);
				pthread_mutex_unlock(&d->print);
			}
			pthread_mutex_unlock(&d->death);
			pthread_mutex_unlock(&d->philos[i].meal_time_lock);
			*someone_died = 1;
			return ;
		}
		if (d->must_eat > 0 && d->philos[i].meals_eaten >= d->must_eat)
			(*full_count)++;
		pthread_mutex_unlock(&d->philos[i].meal_time_lock);
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			full_count;
	int			someone_died;
	long long	now;

	now = 0;
	data = (t_data *)arg;
	while (1)
	{
		usleep(500);
		full_count = 0;
		someone_died = 0;
		monitor_loop(data, &full_count, &someone_died, now);
		if (someone_died)
			return (NULL);
		if (data->must_eat > 0 && full_count == data->num_philos)
		{
			pthread_mutex_lock(&data->death);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->death);
			return (NULL);
		}
	}
}

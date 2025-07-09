/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:59:02 by aerenler          #+#    #+#             */
/*   Updated: 2025/07/01 16:59:02 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_time_lock);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	think_routine(t_philo *philo, int silent)
{
	long long	delta;

	pthread_mutex_lock(&philo->meal_time_lock);
	delta = (philo->data->time_to_die
			- (get_time() - philo->last_meal)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (delta < 0)
		delta = 0;
	if (silent && delta == 0)
		delta = 1;
	if (delta > 600)
		delta = 200;
	if (!silent)
		print_status(philo, "is thinking");
	ft_usleep(delta, philo);
}

void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (NULL);
}

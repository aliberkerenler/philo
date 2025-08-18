/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:08:06 by aerenler          #+#    #+#             */
/*   Updated: 2025/07/01 18:08:06 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	int				meals_eaten;
	pthread_mutex_t	meal_time_lock;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

void		*lone_philo_routine(t_philo *philo);
void		think_routine(t_philo *philo, int silent);
void		eat_sleep_routine(t_philo *philo);

void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);

long long	get_time(void);
int			ft_atoi(const char *str);
void		ft_usleep(long long time_in_ms, t_philo *philo);
void		print_status(t_philo *philo, char *status);
void		cleanup(t_data *data);

int			init_data(t_data *data);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data);

int			parse_args(t_data *data, int argc, char **argv);

#endif
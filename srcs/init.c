/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:04:49 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 03:56:20 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, int tid, t_data *data)
{
	philo->data = data;
	philo->tid = tid;
	philo->death_time = get_time() + data->time_to_die;
	philo->is_eating = 0;
	philo->is_dead = 0;
	philo->meals = 0;
	philo->stop = 0;
	if (pthread_mutex_init(&(philo->fork), NULL))
		return (panic(ERR_MUTEX, 3, tid, data));
	if (pthread_mutex_init(&(philo->death_time_lock), NULL))
		return (panic(ERR_MUTEX, 3, tid, data));
	if (pthread_mutex_init(&(philo->stop_lock), NULL))
		return (panic(ERR_MUTEX, 3, tid, data));
	philo->next = NULL;
	if (philo->tid == data->n_philo)
		philo->next = data->philos;
	return (0);
}

int	init_philos(t_data *data)
{
	int		i;
	t_philo	*new;

	i = 1;
	data->philos = (t_philo *){0};
	while (i <= data->n_philo)
	{
		new = malloc(sizeof(t_philo));
		if (!new)
			return (panic(ERR_MALLOC, 3, i, data));
		if (init_philo(new, i, data))
			return (1);
		ft_lstadd_back(&(data->philos), new);
		i++;
	}
	return (0);
}

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	tid;
	t_philo		*philos;

	i = 1;
	philos = data->philos;
	while (i <= data->n_philo)
	{
		if (pthread_create(&(philos->tphilo), NULL, routine, philos))
			return (panic(ERR_THREAD, 3, data->n_philo, data));
		philos = philos->next;
		i++;
	}
	if (data->n_philo == 1)
	{
		pthread_create(&tid, NULL, monitoring_one, (void *)data);
		pthread_join(tid, NULL);
	}
	else
	{
		pthread_create(&tid, NULL, monitoring, (void *)data);
		pthread_join(tid, NULL);
	}
	return (0);
}

int	init_data(int ac, char **av, t_data *data)
{
	data->n_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->n_meals = -1;
	data->is_dead = 0;
	data->start_time = get_time();
	if (ac == 6)
		data->n_meals = ft_atoi(av[4]);
	if (pthread_mutex_init(&(data->write), NULL))
		return (panic(ERR_MUTEX, 1, 0, data));
	if (pthread_mutex_init(&(data->eat), NULL))
		return (panic(ERR_MUTEX, 2, 0, data));
	if (pthread_mutex_init(&(data->dead), NULL))
		return (panic(ERR_MUTEX, 3, 0, data));
	if (init_philos(data))
		return (1);
	return (init_threads(data));
}

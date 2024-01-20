/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:30:00 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 04:00:49 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_has_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	philo->data->is_dead = 1;
	pthread_mutex_unlock(&philo->data->dead);
	pthread_mutex_lock(&philo->data->write);
	printf("%li %d %s\n", get_time() - philo->data->start_time, philo->tid,
		DEAD);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_unlock(&philo->death_time_lock);
}

void	*monitoring(void *vdata)
{
	t_data	*data;
	int		i;
	t_philo	*philos;

	data = (t_data *)vdata;
	philos = data->philos;
	while (!data->is_dead)
	{
		i = 1;
		while (i <= data->n_philo)
		{
			pthread_mutex_lock(&philos->death_time_lock);
			if (get_time() >= philos->death_time)
			{
				philo_has_died(philos);
				return (NULL);
			}
			pthread_mutex_unlock(&philos->death_time_lock);
			philos = philos->next;
			i++;
		}
		if (all_eaten(data))
			return (NULL);
	}
	return (NULL);
}

int	all_eaten_one(t_data *data)
{
	int		i;
	int		c;
	t_philo	*philos;

	c = 0;
	i = 1;
	if (data->n_meals == -1)
		return (0);
	philos = data->philos;
	pthread_mutex_lock(&data->eat);
	if (philos->meals >= data->n_meals)
		c++;
	pthread_mutex_unlock(&data->eat);
	return (c);
}

void	*monitoring_one(void *vdata)
{
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)vdata;
	philos = data->philos;
	while (!data->is_dead)
	{
		pthread_mutex_lock(&philos->death_time_lock);
		if (get_time() >= philos->death_time)
		{
			philo_has_died(philos);
			return (NULL);
		}
		pthread_mutex_unlock(&philos->death_time_lock);
		if (all_eaten_one(data))
			return (NULL);
	}
	return (NULL);
}

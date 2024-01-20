/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 23:02:13 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 03:39:34 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_data *data)
{
	int		i;
	int		c;
	t_philo	*philos;

	c = 0;
	i = 1;
	if (data->n_meals == -1)
		return (0);
	philos = data->philos;
	while (i <= data->n_philo)
	{
		pthread_mutex_lock(&data->eat);
		if (philos->meals >= data->n_meals)
			c++;
		pthread_mutex_unlock(&data->eat);
		i++;
		philos = philos->next;
	}
	if (c == data->n_philo)
		return (1);
	return (0);
}

int	is_dead(t_data *data)
{
	int	b;

	b = 0;
	pthread_mutex_lock(&(data->dead));
	if (data->is_dead)
		b = 1;
	pthread_mutex_unlock(&(data->dead));
	return (b);
}

void	*set_stop(t_philo *philo)
{
	pthread_mutex_lock(&(philo->stop_lock));
	philo->stop = 1;
	pthread_mutex_unlock(&(philo->stop_lock));
	return (NULL);
}

void	*routine(void *vphilo)
{
	t_philo	*philo;

	philo = (t_philo *)vphilo;
	if (philo->tid % 2 == 0)
		usleep(50);
	while (!is_dead(philo->data))
	{
		if (is_dead(philo->data) || all_eaten(philo->data))
			return (set_stop(philo));
		eat(philo);
		if (is_dead(philo->data) || all_eaten(philo->data))
			return (set_stop(philo));
		psleep(philo);
		if (is_dead(philo->data) || all_eaten(philo->data))
			return (set_stop(philo));
		think(philo);
		if (is_dead(philo->data) || all_eaten(philo->data))
			return (set_stop(philo));
	}
	return (set_stop(philo));
}

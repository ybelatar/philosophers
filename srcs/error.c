/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:30:35 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 03:38:50 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_data(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 1;
	while (i <= data->n_philo)
	{
		if (i < data->n_philo)
			tmp = data->philos->next;
		pthread_mutex_destroy(&data->philos->fork);
		pthread_mutex_destroy(&data->philos->death_time_lock);
		pthread_mutex_destroy(&data->philos->stop_lock);
		pthread_join(data->philos->tphilo, NULL);
		free(data->philos);
		i++;
		data->philos = tmp;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->dead);
}

int	data_mutex(t_data *data, int n)
{
	if (n == 3)
		pthread_mutex_destroy(&data->dead);
	if (n >= 2)
		pthread_mutex_destroy(&data->eat);
	if (n >= 1)
		pthread_mutex_destroy(&data->write);
	return (1);
}

int	panic(char *str, int dmutex, int nthread, t_data *data)
{
	int		i;
	t_philo	*tmp;

	ft_putstr_fd(2, str);
	data_mutex(data, dmutex);
	i = 1;
	while (i <= nthread)
	{
		if (i < data->n_philo)
			tmp = data->philos->next;
		pthread_mutex_destroy(&data->philos->fork);
		pthread_mutex_destroy(&data->philos->death_time_lock);
		pthread_mutex_destroy(&data->philos->stop_lock);
		pthread_join(data->philos->tphilo, NULL);
		free(data->philos);
		i++;
		data->philos = tmp;
	}
	return (1);
}

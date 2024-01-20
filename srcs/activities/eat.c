/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:37:42 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 03:53:52 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	odd_eating(t_philo *philo)
{
	if (philo->data->n_philo == 1)
		return ;
	pthread_mutex_lock(&(philo->next->fork));
	message(philo, FORK);
	pthread_mutex_lock(&(philo->fork));
	message(philo, FORK);
	message(philo, EAT);
	pthread_mutex_lock(&(philo->data->eat));
	philo->meals++;
	pthread_mutex_unlock(&(philo->data->eat));
	msleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&(philo->next->fork));
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_lock(&philo->death_time_lock);
	philo->death_time = get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->death_time_lock);
}

void	even_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork));
	message(philo, FORK);
	pthread_mutex_lock(&(philo->next->fork));
	message(philo, FORK);
	message(philo, EAT);
	pthread_mutex_lock(&(philo->data->eat));
	philo->meals++;
	pthread_mutex_unlock(&(philo->data->eat));
	msleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(&(philo->next->fork));
	pthread_mutex_lock(&philo->death_time_lock);
	philo->death_time = get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->death_time_lock);
}

void	eat(t_philo *philo)
{
	if (philo->tid % 2)
		odd_eating(philo);
	else
		even_eating(philo);
}

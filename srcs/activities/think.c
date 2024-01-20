/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:43:51 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 03:39:02 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	message(philo, THINK);
	if (philo->data->n_philo % 2 != 0)
		msleep(philo->data->time_to_eat / 10, philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:08:52 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 01:28:25 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(long int time, t_philo *philo)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
	(void)philo;
}

int	ft_strcmp(char *s1, char *s2)
{
	while (!s1 && !s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

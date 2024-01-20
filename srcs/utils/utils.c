/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:28:46 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 04:04:02 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstlast(t_philo *philos)
{
	while (philos)
	{
		if (!philos->next)
			return (philos);
		philos = philos->next;
	}
	return (philos);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

void	ft_putstr_fd(int fd, char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &(str[i]), 1);
		i++;
	}
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead || all_eaten(philo->data))
	{
		pthread_mutex_unlock(&philo->data->dead);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead);
	pthread_mutex_lock(&(philo->data->write));
	printf("%li %d %s", get_time() - philo->data->start_time, philo->tid, str);
	pthread_mutex_unlock(&(philo->data->write));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:23:29 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 03:37:22 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_stopped(t_data *data)
{
	int		i;
	int		c;
	t_philo	*philos;

	c = 0;
	i = 1;
	philos = data->philos;
	while (i <= data->n_philo)
	{
		pthread_mutex_lock(&philos->stop_lock);
		if (philos->stop)
			c++;
		pthread_mutex_unlock(&philos->stop_lock);
		i++;
		philos = philos->next;
	}
	if (c == data->n_philo)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	static t_data	data = {0};

	if (ac < 5 || ac > 6)
	{
		printf("Error\nWrong number of arguments\n");
		return (0);
	}
	if (valid_input(ac, av, &data))
		return (0);
	if (init_data(ac, av + 1, &data))
		return (0);
	while (1)
	{
		usleep(5000);
		if (all_stopped(&data))
			break ;
	}
	clean_data(&data);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:46:42 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/22 04:07:41 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*Some colors*/
# define NC "\e[0m"
# define YELLOW "\e[1;33m"

# define ERR_ARG "Error\nInvalid arguments\n"
# define ERR_MALLOC "Error\nMalloc failure\n"
# define ERR_MUTEX "Error\nMutex manipulation failure\n"
# define ERR_THREAD "Error\nThread manipulation failure\n"

# define EAT "is eating\n"
# define FORK "has taken a fork\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DEAD "died\n"
# define MEALS_DONE "All meals have been eaten"

/*We define the data structure beforehand
because it is used by the philo structure*/
struct	s_data;

/*Individual philosopher structure*/
typedef struct s_philo
{
	struct s_data	*data;
	int				tid;
	int				meals;
	int				is_eating;
	int				is_dead;
	long int		death_time;
	int				n_meals;
	int				stop;
	pthread_t		tphilo;
	pthread_mutex_t	fork;
	pthread_mutex_t	death_time_lock;
	pthread_mutex_t	stop_lock;
	struct s_philo	*next;
}					t_philo;

/*Overall structure containing global intel and more*/
typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				is_dead;
	long int		start_time;
	struct s_philo	*philos;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
}					t_data;

/*Parsing*/
int					valid_input(int ac, char **av, t_data *data);

/*Initializing*/
int					init_data(int ac, char **av, t_data *data);

/*Threads*/
void				*routine(void *vphilo);
void				*monitoring(void *vdata);
void				*monitoring_one(void *vdata);
void				eat(t_philo *philo);
void				psleep(t_philo *philo);
void				think(t_philo *philo);

/*Free*/
int					panic(char *str, int dmutex, int nthread, t_data *data);
void				clean_data(t_data *data);

/*Utils*/
void				ft_putstr_fd(int fd, char *str);
int					ft_atoi(const char *str);
void				ft_lstadd_back(t_philo **lst, t_philo *new);
long				get_time(void);
void				message(t_philo *philo, char *str);
void				msleep(long time, t_philo *philo);
int					ft_strcmp(char *s1, char *s2);
int					is_dead(t_data *data);
int					all_eaten(t_data *data);

#endif

/*./philo 3 610 200 100      vol fourchette arabic*/
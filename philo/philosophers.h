/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:46:09 by kbrauer           #+#    #+#             */
/*   Updated: 2024/02/23 17:01:27 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>  // thread, mutex
# include <stdlib.h>   // malloc, free
# include <stdio.h>    // printf
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // usleep
# include <limits.h>   // INT_MAX

# define ERROR_ARG1 "Wrong number of arguments!"
# define ERROR_ARG2 "Arguments not correct!"
# define ERROR_ARG3 "Arguments cannot be negative!"
# define ERROR_ARG4 "Arguments cannot be bigger than INT!"
# define ERROR_ARG5 "Arguments cannot be zero!"

# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"
# define FORK "has taken a fork"

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				philo_id;
	long			eattime;
	int				meals_ate;
	t_table			*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		tid;
}	t_philo;

typedef struct s_table
{
	long			philo_num;
	long			ttdie;
	long			tteat;
	long			ttsleep;
	long			philo_max_eat;
	long			start_time;
	int				done_eating;
	int				dead;
	t_philo			*philo;
	t_fork			*forks;
	pthread_mutex_t	lock_t;
	pthread_t		mon;
}	t_table;

//free.c
void	free_all(t_table *table);

//utils.c
int		ft_usleep(useconds_t time);
int		ft_print(char *str, t_philo *philo);
int		check_length(char *str);
long	ft_atol(const char *nptr);
long	get_time(void);

//init.c
int		init_data(t_table *data, char **argv);
int		create_table(t_table *table);
int		mal_all(t_table *table);
void	init_values(t_table *data, char **argv);

//sim.c
int		eating(t_philo *philo);
int		take_forks(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	init_philo(int i, t_table *table);
void	simulation(t_table *table);
void	*monitor(void *philo_void);
void	*routine(void *philo_void);

#endif
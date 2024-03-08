/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:47:19 by kbrauer           #+#    #+#             */
/*   Updated: 2024/02/22 17:46:06 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_values(t_table *data, char **argv)
{
	data->philo_num = ft_atol(argv[1]);
	data->ttdie = ft_atol(argv[2]);
	data->tteat = ft_atol(argv[3]);
	data->ttsleep = ft_atol(argv[4]);
	if (argv[5])
		data->philo_max_eat = ft_atol(argv[5]);
	else
		data->philo_max_eat = 0;
	data->philo = NULL;
	data->forks = NULL;
	data->dead = 0;
	data->done_eating = 0;
}

int	init_data(t_table *data, char **argv)
{
	init_values(data, argv);
	if (data->philo_num == -1
		|| data->ttdie == -1
		|| data->tteat == -1
		|| data->ttsleep == -1
		|| data->philo_max_eat == -1)
		return (printf(ERROR_ARG3), 1);
	if (data->philo_num == -2
		|| data->ttdie == -2
		|| data->tteat == -2
		|| data->ttsleep == -2
		|| data->philo_max_eat == -2)
		return (printf(ERROR_ARG4), 1);
	if (data->philo_num == -3
		|| data->ttdie == -3
		|| data->tteat == -3
		|| data->ttsleep == -3
		|| data->philo_max_eat == -3)
		return (printf(ERROR_ARG5), 1);
	return (0);
}

int	mal_all(t_table *table)
{
	int	n;

	n = table->philo_num;
	table->forks = (t_fork *) malloc (sizeof(t_fork) * n);
	if (!table->forks)
		return (-1);
	table->philo = (t_philo *) malloc (sizeof(t_philo) * n);
	if (!table->philo)
		return (free(table->forks), -1);
	return (0);
}

void	init_philo(int i, t_table *table)
{
	table->forks[i].fork_id = i;
	table->philo[i].philo_id = i;
	table->philo[i].eattime = 0;
	table->philo[i].meals_ate = 0;
	table->philo[i].table = table;
	table->philo[i].tid = 0;
	table->philo[i].left_fork = &table->forks[i].fork;
	if (table->philo_num != 1)
	{
		if (i == 0)
			table->philo[i].r_fork = &table->forks[table->philo_num - 1].fork;
		else
			table->philo[i].r_fork = &table->forks[i - 1].fork;
	}
	else
		table->philo[i].r_fork = NULL;
}

int	create_table(t_table *table)
{
	int	i;

	i = -1;
	if (mal_all(table))
		return (-1);
	table->start_time = get_time();
	pthread_mutex_init(&table->lock_t, NULL);
	while (++i < table->philo_num)
		pthread_mutex_init(&table->forks[i].fork, NULL);
	i = -1;
	while (++i < table->philo_num)
		init_philo(i, table);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:48:03 by kbrauer           #+#    #+#             */
/*   Updated: 2024/02/28 18:10:26 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

int	take_forks(t_philo *philo)
{
	if (philo->table->philo_num == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(FORK, philo);
		pthread_mutex_lock(&philo->table->lock_t);
		philo->eattime = get_time();
		pthread_mutex_unlock(&philo->table->lock_t);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(FORK, philo);
		pthread_mutex_lock(philo->r_fork);
		ft_print(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print(FORK, philo);
		pthread_mutex_lock(philo->left_fork);
		ft_print(FORK, philo);
	}
	return (0);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;
	int		dead;

	philo = philo_void;
	if (philo->philo_id % 2)
		usleep(9000);
	pthread_mutex_lock(&philo->table->lock_t);
	dead = philo->table->dead;
	pthread_mutex_unlock(&philo->table->lock_t);
	while (!dead)
	{
		if (eating(philo))
			return (NULL);
		pthread_mutex_lock(&philo->table->lock_t);
		philo->meals_ate++;
		pthread_mutex_unlock(&philo->table->lock_t);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&philo->table->lock_t);
		dead = philo->table->dead;
		pthread_mutex_unlock(&philo->table->lock_t);
	}
	return (NULL);
}

void	monitor_helper(t_table *table)
{
	int		i;
	long	time;

	i = -1;
	while (++i < table->philo_num)
	{
		pthread_mutex_lock(&table->lock_t);
		time = table->philo[i].eattime;
		pthread_mutex_unlock(&table->lock_t);
		if (time)
		{
			if ((get_time() - time) > table->ttdie)
			{
				ft_print(DEAD, &table->philo[i]);
				pthread_mutex_lock(&table->lock_t);
				table->dead = 1;
				pthread_mutex_unlock(&table->lock_t);
			}
		}
	}
}

void	*monitor(void *table_void)
{
	t_table	*table;
	int		dead;

	table = table_void;
	pthread_mutex_lock(&table->lock_t);
	dead = table->dead;
	pthread_mutex_unlock(&table->lock_t);
	while (!dead)
	{
		usleep(100);
		monitor_helper(table);
		pthread_mutex_lock(&table->lock_t);
		if (table->done_eating >= table->philo_num)
			table->dead = 1;
		dead = table->dead;
		pthread_mutex_unlock(&table->lock_t);
	}
	return (NULL);
}

void	simulation(t_table *table)
{
	int	i;

	i = -1;
	pthread_create(&table->mon, NULL, &monitor, table);
	while (++i < table->philo_num)
		pthread_create(&table->philo[i].tid, NULL,
			&routine, &table->philo[i]);
	i = -1;
	while (++i < table->philo_num)
		pthread_join(table->philo[i].tid, NULL);
	pthread_join(table->mon, NULL);
}

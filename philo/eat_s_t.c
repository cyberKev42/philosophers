/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_s_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:27:35 by kbrauer           #+#    #+#             */
/*   Updated: 2024/02/23 16:57:49 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	ft_print(EATING, philo);
	pthread_mutex_lock(&philo->table->lock_t);
	if (philo->table->philo_max_eat != 0)
	{
		if (philo->meals_ate == philo->table->philo_max_eat)
			philo->table->done_eating++;
	}
	philo->eattime = get_time();
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->lock_t);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->lock_t);
	ft_usleep(philo->table->tteat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	sleeping(t_philo *philo)
{
	ft_print(SLEEPING, philo);
	ft_usleep(philo->table->ttsleep);
}

void	thinking(t_philo *philo)
{
	ft_print(THINKING, philo);
	ft_usleep(1);
}

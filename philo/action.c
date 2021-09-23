/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:37:33 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/20 12:37:48 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *philo)
{
	int	bias;

	pthread_mutex_lock(philo->l_fork);
	ft_print_status(ft_get_time() - philo->start, philo, " has taken a fork\n");
	pthread_mutex_lock(philo->r_fork);
	bias = ft_get_time();
	ft_print_status(ft_get_time() - philo->start, philo, " has taken a fork\n");
	philo->is_eating = 1;
	philo->bias = ft_get_time() + philo->time_to_die;
	ft_print_status(ft_get_time() - philo->start, philo, " is eating\n");
	bias = ft_get_time() - bias;
	ft_usleep(philo->time_to_eat - bias);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->eat_count++;
	philo->is_eating = 0;
	if (philo->eat_count == philo->times_eat)
		philo->id = 0;
}

static void	ft_routine(t_philo *philo)
{
	int	bias;

	bias = 0;
	ft_eat(philo);
	while (philo->id != 0)
	{
		bias = ft_get_time();
		ft_print_status(ft_get_time() - philo->start, philo, " is sleeping\n");
		bias = ft_get_time() - bias;
		ft_usleep(philo->time_to_sleep - bias);
		ft_print_status(ft_get_time() - philo->start, philo, " is thinking\n");
		ft_eat(philo);
	}
}

void	*ft_run(void *philo_arg)
{
	t_philo		*philo;

	philo = (t_philo *)(philo_arg);
	philo->start = ft_get_time();
	philo->bias = ft_get_time() + philo->time_to_die;
	ft_routine(philo);
	philo->id = 0;
	return (NULL);
}

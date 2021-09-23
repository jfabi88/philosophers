/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:19:28 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/20 16:19:31 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork_to_philo(t_state *state, t_philo *philo, int id)
{
	if (id == state->num_philos)
	{
		philo->r_fork = state->forks[id - 1];
		philo->l_fork = state->forks[0];
	}
	else
	{
		philo->l_fork = state->forks[id - 1];
		philo->r_fork = state->forks[id];
	}
}

int	ft_free_state(t_state *state)
{
	int	i;

	if (state->forks)
	{
		i = 0;
		while (i < state->num_philos)
		{
			pthread_mutex_destroy(state->forks[i]);
			i++;
		}
	}
	ft_free_m((void **)(state->forks));
	ft_free_m((void **)(state->philos));
	if (state->philo_death)
	{
		free(state->philo_death);
		pthread_mutex_destroy(state->philo_death);
	}
	if (state->print)
	{
		free(state->print);
		pthread_mutex_destroy(state->print);
	}
	return (1);
}

void	ft_usleep(int time)
{
	int	end;

	end = ft_get_time() + time;
	while (ft_get_time() < end)
		usleep(time);
}

void	ft_free_m(void **mtx)
{
	int	i;

	i = 0;
	if (mtx)
	{
		while (mtx[i])
		{
			free(mtx[i]);
			i++;
		}
	}
	free(mtx);
}

int	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int)(tv.tv_sec * 1000) + (int)(tv.tv_usec / 1000));
}

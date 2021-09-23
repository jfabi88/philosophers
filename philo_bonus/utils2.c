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

int	ft_free_state(t_state *state)
{
	int	i;

	i = 0;
	if (state->forks)
		sem_unlink("fork");
	if (state->philo_death)
		sem_unlink("death");
	if (state->print)
		sem_unlink("print");
	while (state->philos[i])
	{
		kill(state->philos[i]->pid, SIGINT);
		i++;
	}
	ft_free_m((void **)(state->philos));
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

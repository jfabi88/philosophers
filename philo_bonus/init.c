/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:47:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/20 11:48:01 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_philos(t_state *state)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < state->num_philos)
	{
		philo = state->philos[i];
		philo->id = i + 1;
		philo->eat_count = 0;
		philo->time_to_die = state->time_to_die;
		philo->time_to_eat = state->time_to_eat;
		philo->time_to_sleep = state->time_to_sleep;
		philo->l_fork = state->forks;
		philo->r_fork = state->forks;
		philo->death = state->philo_death;
		philo->print = state->print;
		philo->is_eating = 0;
		philo->tot = state->num_philos;
		philo->times_eat = state->num_eat;
		philo->eat_times = state->eat_count;
		i++;
	}
	return (0);
}

static int	ft_malloc_philo(t_state *state)
{
	t_philo	**m_philo;
	int		i;

	i = 0;
	m_philo = (t_philo **)malloc(sizeof(t_philo *) * (state->num_philos + 1));
	if (m_philo == NULL)
		return (1);
	while (i < state->num_philos)
	{
		m_philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (m_philo == NULL)
		{
			ft_free_m((void **)m_philo);
			return (1);
		}
		i++;
	}
	m_philo[i] = NULL;
	state->philos = m_philo;
	return (0);
}

int	ft_init(t_state *state, int argc, char *argv[])
{
	sem_unlink("exit");
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("death");
	sem_unlink("eat");
	state->num_philos = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->num_eat = 0;
	if (argc == 6)
		state->num_eat = ft_atoi(argv[5]);
	state->forks = NULL;
	state->print = NULL;
	state->philo_death = NULL;
	if (ft_malloc_philo(state))
		return (1);
	state->exit = sem_open("exit", O_CREAT, 0644, 1);
	state->forks = sem_open("fork", O_CREAT, 0644, state->num_philos);
	state->print = sem_open("print", O_CREAT, 0644, 1);
	state->philo_death = sem_open("death", O_CREAT, 0644, 0);
	state->eat_count = sem_open("eat", O_CREAT, 0644, 1);
	ft_init_philos(state);
	return (0);
}

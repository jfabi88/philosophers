/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:25:16 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/20 11:25:18 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(int time, t_philo *philo, char *s)
{
	sem_t			*print;

	print = philo->print;
	sem_wait(print);
	ft_putnbr(time);
	write(1, ": ", 2);
	ft_putnbr(philo->id);
	write(1, s, ft_strlen(s));
	if (s[1] != 'd')
		sem_post(print);
}

void	*ft_cheack_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->id != 0)
	{
		if (!philo->is_eating && ft_get_time() > philo->bias)
		{
			ft_print_status(ft_get_time() - philo->start, philo, " died\n");
			sem_post(philo->death);
			return (NULL);
		}
	}
	return (NULL);
}

static void	*ft_count(void *arg)
{
	t_state	*state;
	int		flag;
	int		i;

	state = (t_state *)arg;
	i = 0;
	while (i < state->num_philos)
	{
		sem_wait(state->eat_count);
		i++;
	}
	sem_post(state->philo_death);
	return ((void *)0);
}

static int	ft_run_philo(t_state *state)
{
	int			i;
	pthread_t	pth;
	pthread_t	eat_count;

	i = 0;
	if (pthread_create(&eat_count, NULL, &ft_count, (void *)(state)))
		return (ft_error(3));
	pthread_detach(eat_count);
	while (i < state->num_philos)
	{
		state->philos[i]->pid = fork();
		if (state->philos[i]->pid < 0)
			return (1);
		else if (state->philos[i]->pid == 0)
		{
			ft_run(state->philos[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_state	state;

	if (ft_check_philo(argc, argv))
		return (1);
	if (ft_init(&state, argc, argv))
		return (ft_free_state(&state));
	if (ft_run_philo(&state))
		return (ft_free_state(&state));
	sem_wait(state.philo_death);
	sem_wait(state.exit);
	ft_free_state(&state);
	return (0);
}

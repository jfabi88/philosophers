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
	pthread_mutex_t	*print;

	print = philo->print;
	pthread_mutex_lock(print);
	ft_putnbr(time);
	write(1, ": ", 2);
	ft_putnbr(philo->id);
	write(1, s, ft_strlen(s));
	if (s[1] != 'd')
		pthread_mutex_unlock(print);
}

static void	*ft_cheack_death(void *arg)
{
	t_state	*state;
	t_philo	*pil;
	int		i;

	state = (t_state *)arg;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&state->exit);
		while (state->philos[i])
		{
			pil = state->philos[i];
			if (pil->bias != -1)
			{
				if (!pil->is_eating && ft_get_time() > pil->bias)
				{
					ft_print_status(ft_get_time() - pil->start, pil, " died\n");
					pthread_mutex_unlock(pil->death);
				}
				i++;
			}
		}
		pthread_mutex_unlock(&state->exit);
	}
}

static void	*ft_count(void *arg)
{
	t_state	*state;
	int		flag;
	int		i;

	state = (t_state *)arg;
	flag = 1;
	while (flag != 0 && state)
	{
		pthread_mutex_lock(&state->exit);
		i = 0;
		flag = 0;
		while (state->philos[i])
		{
			if (state->philos[i]->id != 0)
				flag = 1;
			i++;
		}
		pthread_mutex_unlock(&state->exit);
	}
	pthread_mutex_unlock(state->philo_death);
	return ((void *)0);
}

static int	ft_run_philo(t_state *state)
{
	int			i;
	pthread_t	pth;
	pthread_t	eat_count;
	pthread_t	death;

	i = 0;
	if (pthread_create(&eat_count, NULL, &ft_count, (void *)(state)))
		return (ft_error(3));
	pthread_detach(eat_count);
	if (pthread_create(&death, NULL, &ft_cheack_death, (void *)(state)))
		return (ft_error(3));
	pthread_detach(death);
	while (i < state->num_philos)
	{
		if (pthread_create(&pth, NULL, &ft_run, (void *)(state->philos[i])))
			return (ft_error(3));
		pthread_detach(pth);
		i++;
	}
	pthread_detach(pth);
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
	pthread_mutex_lock(state.philo_death);
	pthread_mutex_unlock(state.philo_death);
	pthread_mutex_lock(&state.exit);
	ft_free_state(&state);
	return (0);
}

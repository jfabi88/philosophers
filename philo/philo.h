/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:24:08 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/20 11:24:12 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				last_eat;
	int				bias;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				is_eating;
	int				start;
	int				tot;
	int				times_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
}				t_philo;

typedef struct s_state
{
	int				num_philos;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				num_eat;
	int				start_time;
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*philo_death;
	pthread_mutex_t	exit;

}				t_state;

void	ft_print_status(int time, t_philo *philo, char *s);

/* action */
void	*ft_run(void *philo_arg);

/* check_parse */
int		ft_check_philo(int argc, char *argv[]);

/* error */
int		ft_error(int num);

/* init */
int		ft_init(t_state *state, int argc, char *argv[]);

/* utils */
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	ft_putnbr(int n);

/* utils2 */
int		ft_get_time(void);
void	ft_free_m(void **mtx);
void	ft_usleep(int time);
int		ft_free_state(t_state *state);
void	ft_fork_to_philo(t_state *state, t_philo *philo, int id);

#endif
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
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

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
	int				pid;
	sem_t			*r_fork;
	sem_t			*l_fork;
	sem_t			*print;
	sem_t			*death;
	sem_t			*eat_times;
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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*philo_death;
	sem_t			*exit;
	sem_t			*eat_count;

}				t_state;

void	ft_print_status(int time, t_philo *philo, char *s);
void	*ft_cheack_death(void *arg);

/* action */
int		ft_run(t_philo *philo);

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

#endif
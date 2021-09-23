/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:35:29 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/20 11:35:31 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_number(char *str)
{
	int	i;
	int	num;
	int	val;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		val = str[i] - 48;
		if ((2147483647 - val) / 10 < num)
			return (-1);
		num = (num * 10) + val;
		i++;
	}
	return (1);
}

static int	ft_are_numbers(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_is_number(argv[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_check_philo(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ft_error(0));
	if (ft_are_numbers(argc, argv) == -1)
		return (ft_error(1));
	return (0);
}

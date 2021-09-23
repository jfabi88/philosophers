/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:26:34 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/20 11:26:47 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_error_5(int num)
{
	if (num == 0)
		write(2, "error: number of arguments is wrong\n", 36);
	else if (num == 1)
		write(2, "error: bad arguments\n", 21);
	else if (num == 2)
		write(2, "error: mallor\n", 14);
	else if (num == 3)
		write(2, "error: pthread\n", 15);
}

int	ft_error(int num)
{
	if (num >= 0 && num < 5)
		ft_error_5(num);
	return (1);
}

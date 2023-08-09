/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.0.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:03:49 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/09 13:26:38 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static long	result(char *str, int singn, int i)
{
	long	y;
	long	k;

	y = 0;
	k = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		y = y * 10 + str[i] - 48;
		if (k > y)
			ft_print_exit_err();
		k = y;
		if (y > LONG_MAX && singn == -1)
			return (0);
		else if (y > LONG_MAX && singn == 1)
			return (-1);
		i++;
	}
	return (y);
}

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	y;

	i = 0;
	y = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	y = result(str, sign, i);
	return (y * sign);
}

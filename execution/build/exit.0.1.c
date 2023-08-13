/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.0.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:03:49 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 00:14:35 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

// static long	result(char *str, int singn, int i)
// {
// 	long long	y;
// 	long long	k;

// 	y = 0;
// 	k = 0;
// 	(void)singn;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		y = y * 10 + str[i] - 48;
// 		i++;
// 	}
// 	// if (y * singn < __LONG_MIN__)
// 	// 		ft_print_exit_err(str);
// 	// if (y > __LONG_MAX__)
// 	// 	ft_print_exit_err(str);
// 	printf("y: %lld\n", y);
// 	return ((long)y);
// }

// long	ft_atoi(char *str)
// {
// 	int		i;
// 	int		sign;
// 	long	y;

// 	i = 0;
// 	y = 0;
// 	sign = 1;
// 	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	y = result(str, sign, i);
// 	return (y * sign);
// }



long	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	if (res > 9223372036854775807 && sign == 1)
		ft_print_exit_err(str);
	if (res > 9223372036854775808U && sign == -1)
		ft_print_exit_err(str);
	return (res * sign);
}
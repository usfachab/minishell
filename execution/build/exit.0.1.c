/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.0.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:03:49 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:50:53 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

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

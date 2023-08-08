/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.0.0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:55:29 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/08 14:04:08 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_print_exit_err(void)
{
	write (2, "exit\n", 5);
	write (2, "exit: numeric argument required\n", 32);
	g_glob.exit_status = 255;
	exit(255);
}

long	result(char *str, int singn, int i)
{
	long	y;
	long	k;

	y = 0;
	k = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		y = y * 10 + str[i] - 48;
		if (k > y)
		k = y;
		ft_print_exit_err();
		if (y > LONG_MAX && singn == -1)
			return (0);
		else if (y > LONG_MAX && singn == 1)
			return (-1);
		i++;
	}
	return (y);
}

int	ft_just_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		if (!isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit_help(t_parser_var *var)
{
	if (var->data->cmd_args[1]
		&& (ft_just_number(var->data->cmd_args[1])
			|| !var->data->cmd_args[1][0]))
	{
		write (2, "exit\n", 5);
		write (2, "exit: numeric argument required\n", 32);
		g_glob.exit_status = 255;
		exit(255);
	}
	else if (var->data->cmd_args[2])
	{
		write (2, "exit\n", 5);
		write (2, "exit: too many arguments\n", 25);
		g_glob.exit_status = 1;
		return (1);
	}
	else if (var->data->cmd_args[1])
	{
		write (2, "exit\n", 5);
		g_glob.exit_status = ft_atoi(var->data->cmd_args[1]);
		exit(g_glob.exit_status);
	}
	return (0);
}

int	ft_exit(t_data *data, t_parser_var *var)
{
	if (data->cmd_args)
	{
		if (!var->data->cmd_args[1])
		{
			write (2, "exit\n", 5);
			exit (g_glob.exit_status);
		}
		if (ft_exit_help(var))
			return (1);
	}
	return (0);
}

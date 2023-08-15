/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.0.0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:55:29 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:50:41 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_print_exit_err(char *str)
{
	write (2, "exit\n", 5);
	write (2, "minishell: exit: ", 18);
	write (2, str, ft_strlen(str));
	write (2, " numeric argument required\n", 28);
	g_glob.exit_status = 2;
	exit(2);
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

int	ft_exit_help(t_data *data)
{
	if (data->cmd_args[1]
		&& (ft_just_number(data->cmd_args[1])
			|| !data->cmd_args[1][0]))
	{
		write (1, "exit\n", 5);
		write (2, "exit: numeric argument required\n", 32);
		g_glob.exit_status = 2;
		exit(2);
	}
	else if (data->cmd_args[2])
	{
		write (1, "exit\n", 5);
		write (2, "exit: too many arguments\n", 25);
		g_glob.exit_status = 1;
		return (1);
	}
	else if (data->cmd_args[1])
	{
		g_glob.exit_status = ft_atoi(data->cmd_args[1]);
		write (1, "exit\n", 5);
		exit(g_glob.exit_status);
	}
	return (0);
}

int	ft_exit(t_data *data)
{
	if (data->cmd_args)
	{
		if (!data->cmd_args[1])
		{
			write (1, "exit\n", 5);
			exit (g_glob.exit_status);
		}
		if (ft_exit_help(data))
			return (1);
	}
	return (0);
}

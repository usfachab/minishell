/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:07:07 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 01:14:27 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static void	which_builtin(t_parser_var *var, int index, t_data *data)
{
	if (index == 0)
		_pwd();
	else if (index == 1)
		_cd(data->cmd_args);
	else if (index == 2)
		_echo(data->cmd_args);
	else if (index == 3)
		ft_env(g_glob.env);
	else if (index == 4)
		_export(var, data);
	else if (index == 5)
		_unset(data->cmd_args);
	else if (index == 6)
		ft_exit(data);
}

int	run_builtin(t_data *data, t_parser_var *var)
{
	char	*cmds[8];
	int		i;

	cmds[0] = "pwd";
	cmds[1] = "cd";
	cmds[2] = "echo";
	cmds[3] = "env";
	cmds[4] = "export";
	cmds[5] = "unset";
	cmds[6] = "exit";
	cmds[7] = NULL;
	i = 0;
	while (data->cmd_args && data->cmd_args[0] && cmds[i])
	{
		if (!ft_strcmp(data->cmd_args[0], cmds[i]))
		{
			which_builtin(var, i, data);
			return (0);
		}
		i++;
	}
	return (1);
}

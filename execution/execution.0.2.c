/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.0.2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:08:57 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/09 15:33:34 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/minishell.h"

int	count_data(t_parser_var *var)
{
	t_data	*tmp;
	int		i;

	i = 0;
	tmp = var->data;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	var->list_size = i;
	return (i);
}

void	wait__signal(t_parser_var *var, int stat)
{
	int	i;

	i = 0;
	while (i < var->list_size)
	{
		waitpid(var->pid[i], &stat, WUNTRACED);
		if (stat == 0)
			g_glob.exit_status = 0;
		if (WIFSIGNALED(stat))
		{
			if (WTERMSIG(stat) == 2)
			{
				var->flag = -12;
				g_glob.exit_status = 130;
			}
			if (WTERMSIG(stat) == 3)
			{
				var->flag = -13;
				g_glob.exit_status = 131;
			}
		}
		else
			g_glob.exit_status = WEXITSTATUS(stat);
		i++;
	}
}

void	execute(t_parser_var *var, t_data *data, int *fd)
{
	int		i;
	char	*str;
	char	*path;

	i = 0;
	str = NULL;
	_dupping(data, fd);
	if (!run_builtin(data, var))
		return ;
	if (data->cmd_args[0])
	{
		str = ft_strrchr(data->cmd_args[0], '/');
		path = join_with_path(var->splited_path, data, str);
		execve(path, data->cmd_args, var->envp);
		internal_error_msg("minishell: ", errno);
	}
}

void	print_exit(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 28);
	g_glob.exit_status = 127;
	exit(g_glob.exit_status);
}

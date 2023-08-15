/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.0.3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:34:21 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/15 12:04:04 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/minishell.h"

void	ft_main_help(t_parser_var *var, t_data *d, int *fd, int i)
{
	if (var->pid[i] < 0)
		internal_error_msg("", errno);
	if (!var->pid[i])
	{
		if (d->unopened_file == -1)
		{
			g_glob.exit_status = 1;
			exit (1);
		}
		execute_in_child_proc(var, d, fd);
	}
	else
		parent_closing_pipe_part(d, fd);
}

void	ambiguous_error(t_file *file)
{
	write(2, "minishell: ", 11);
	write(2, file->file_name, ft_strlen(file->file_name));
	write(2, ": ambiguous redirect\n", 21);
}

int	fork_fail(int pid)
{
	if (pid < 0)
	{
		perror("minishell: fork: ");
		g_glob.exit_status = 1;
		return (0);
	}
	return (1);
}

int	run_in(char *arg, t_data *d, t_parser_var *v)
{
	if (arg && !ft_strcmp(arg, "cd"))
	{
		_cd(d->cmd_args);
		return (0);
	}
	else if (!d->next && arg && !ft_strcmp(arg, "export") && d->out < 2)
	{
		_export(v, d);
		return (0);
	}
	else if (!d->next && arg && !ft_strcmp(arg, "unset"))
	{
		_unset(d->cmd_args);
		return (0);
	}
	else if (!d->next && arg && !ft_strcmp(arg, "echo") && d->out == 1)
	{
		_echo(d->cmd_args);
		return (0);
	}
	return (1);
}

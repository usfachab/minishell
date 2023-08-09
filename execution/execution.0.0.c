/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.0.0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:19:06 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/09 18:23:19 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/minishell.h"

static void	execute_in_child_proc(t_parser_var *var, t_data *data, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (var->flag == -12)
	{
		g_glob.exit_status = 130;
		exit(g_glob.exit_status);
	}
	if (var->flag == -13)
	{
		g_glob.exit_status = 131;
		exit(g_glob.exit_status);
	}
	execute(var, data, fd);
	exit(0);
}

static void	open_pipe(t_data *data, int *fd)
{
	if (data->next)
	{
		if (pipe(fd) == -1)
			internal_error_msg("", errno);
		if (data->out > 2)
		{
			close(fd[1]);
			fd[1] = data->out;
		}
	}
	else
		fd[1] = data->out;
}

static int	run_built_in_parent(t_data *d, t_parser_var *v)
{
	char	*arg;

	arg = d->cmd_args[0];
	if (v->list_size == 1 && arg && !ft_strcmp(arg, "cd"))
	{
		ft_cd(v, d);
		return (0);
	}
	else if (!d->next && arg && !ft_strcmp(arg, "export"))
	{
		_export(v);
		return (0);
	}
	else if (!d->next && arg && !ft_strcmp(arg, "unset"))
	{
		ft_unset(v);
		return (0);
	}
	else if (!d->next && arg && !ft_strcmp(arg, "echo") && d->out < 2)
	{
		_echo(d->cmd_args);
		g_glob.exit_status = 0;
		return (0);
	}
	return (1);
}

void	ft_main_help(t_parser_var *var, t_data *d, int *fd, int i)
{
	if (var->pid[i] < 0)
		internal_error_msg("", errno);
	if (!var->pid[i])
		execute_in_child_proc(var, d, fd);
	else
		parent_closing_pipe_part(d, fd);
}

static int	main_child_loop(t_parser_var *var, t_data *d, int *fd)
{
	int	i;
	int	j;

	i = 0;
	var->pid = malloc(sizeof(pid_t) * (count_data(var) + 1));
	while (d)
	{
		j = open_file_loop(d);
		if (!j)
		{
			d = d->next;
			continue ;
		}
		if (j == -1)
			return (1);
		if (!d->next && !run_built_in_parent(d, var))
			return (0);
		open_pipe(d, fd);
		var->pid[i] = fork();
		ft_main_help(var, d, fd, i);
		d = d->next;
		i++;
	}
	return (0);
}

void	execution(t_parser_var *var)
{
	int		stat;
	t_data	*d;
	int		fd[2];

	stat = g_glob.exit_status;
	save_last_in_out(var);
	if (heredoc(var))
	{
		var->flag = 0;
		g_glob.interapt_main_signal = -99;
		d = var->data;
		d->in = 0;
		if (!d->next && d->cmd_args[0] && !ft_strcmp(d->cmd_args[0], "exit"))
		{
			ft_exit(d);
			return ;
		}
		if (main_child_loop(var, d, fd))
			return ;
		wait__signal(var, stat);
	}
}

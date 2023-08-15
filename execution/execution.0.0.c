/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.0.0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:19:06 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:52:43 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/minishell.h"

void	execute_in_child_proc(t_parser_var *var, t_data *data, int *fd)
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
	if (d->unopened_file == -1)
		g_glob.exit_status = 1;
	if (!run_in(arg, d, v))
		return (0);
	return (1);
}

static int	main_child_loop(t_parser_var *var, t_data *d)
{
	int	i;
	int	fd[2];

	i = 0;
	fd[0] = -1;
	fd[1] = -1;
	d->prev = -1;
	var->pid = malloc(sizeof(pid_t) * (count_data(var) + 1));
	while (d)
	{
		d->unopened_file = 0;
		open_file_loop(d);
		if (!d->next && var->list_size == 1 && !run_built_in_parent(d, var))
			return (1);
		open_pipe(d, fd);
		var->pid[i] = fork();
		if (!fork_fail(var->pid[i]))
			return (1);
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
		if (main_child_loop(var, d))
			return ;
		wait__signal(var, stat);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.0.1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:32:56 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 18:22:19 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/minishell.h"

static char	*absolute_path(char *cmd)
{
	struct stat	file_stat;

	if (!access(cmd, F_OK))
	{
		if (stat(cmd, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
			{
				write(2, "minishell: ", 11);
				write(2, cmd, ft_strlen(cmd));
				write(2, ": is a directory\n", 17);
				g_glob.exit_status = 126;
				exit(126);
			}
		}
		if (access(cmd, X_OK) == -1)
		{
			write(2, "minishell: ", 11);
			perror(cmd);
			g_glob.exit_status = 126;
			exit(126);
		}
		return (cmd);
	}
	return (NULL);
}

static char	*hanling_path(char *cmd, char **splited_path)
{
	int		i;
	char	*path;

	i = 0;
	if (cmd && !cmd[0])
		external_error_msg("minishell: : command not found\n", 127);
	if (!splited_path)
		print_exit(cmd);
	while (splited_path && splited_path[i])
	{
		path = _join_path(splited_path[i], cmd);
		if (path && !access(path, F_OK) && !access(path, X_OK))
			return (path);
		free(path);
		i++;
	}
	ft_tmp(cmd);
	g_glob.exit_status = 127;
	exit(g_glob.exit_status);
}

char	*join_with_path(char **splited_path, t_data *data, char *str)
{
	if (str != NULL)
	{
		if (absolute_path(data->cmd_args[0]))
			return (data->cmd_args[0]);
		else
		{
			write(2, "minishell: ", 11);
			write(2, data->cmd_args[0], ft_strlen(data->cmd_args[0]));
			write(2, ": No such file or directory\n", 28);
			g_glob.exit_status = 127;
			exit(127);
		}
	}
	return (hanling_path(data->cmd_args[0], splited_path));
}

void	_dupping(t_data *data, int *fd)
{
	if (data->in == 0 && fd[0] > 2)
		close(fd[0]);
	if (data->in > 2)
	{
		if (dup2(data->in, STDIN_FILENO) < 0)
			internal_error_msg("minishell: ", errno);
		close(data->in);
		if (fd[0] > 2)
			close(fd[0]);
	}
	if (fd[1] > 2)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			internal_error_msg("minishell: ", errno);
		close(fd[1]);
	}
}

void	parent_closing_pipe_part(t_data *data, int *fd)
{
	if (data->next)
	{
		close(fd[1]);
		data->next->in = fd[0];
		data->next->prev = fd[0];
	}
	else
	{
		if (data->in != data->prev && data->prev > 2)
			close(data->prev);
	}
	if (data->in > 2)
		close(data->in);
}

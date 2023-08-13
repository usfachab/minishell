/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:59:08 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 19:01:29 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	m_l_h(t_file *file, char *str, char	*expanded)
{
	if (!expanded)
	{
		g_glob.exit_status = 1;
		exit(1);
	}
	if (is_limiter(str, file->file_name))
	{
		g_glob.exit_status = 0;
		exit (0);
	}
}

void	main_loop(t_file *file, char **env, int fd)
{
	char	*str;
	char	*expanded;

	expanded = NULL;
	while (1)
	{
		str = readline("> ");
		if (str && file->type == 5 && ft_strchr(str, '$'))
			expanded = expand(str, env, 1);
		else
			expanded = str;
		m_l_h(file, str, expanded);
		if (fd > 2)
		{
			write(fd, expanded, strlen(expanded));
			write(fd, "\n", 1);
		}
		if (expanded && expanded != str)
			free(expanded);
		free(str);
	}
}

int	piping_forking_h(t_data *data, int *fd)
{
	int	stat;

	stat = 0;
	close(fd[1]);
	data->last_hdc = fd[0];
	while (wait(&stat) > 0)
		;
	if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == 2)
		{
			if (fd[0] != 0)
				close(fd[0]);
			return (0);
		}
	}
	return (1);
}

int	piping_forking(t_data *data, t_file *file, char **env)
{
	int	pid;
	int	fd[2];

	g_glob.interapt_main_signal = -99;
	if (data->last_in && data->last_in == file)
		pipe(fd);
	else
		fd[1] = -1;
	pid = fork();
	if (pid < 0)
		internal_error_msg("", errno);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		if (fd[0] != 0)
			close(fd[0]);
		main_loop(file, env, fd[1]);
		close(fd[1]);
	}
	else
	{
		if (!piping_forking_h(data, fd))
			return (0);
	}
	return (1);
}

bool	heredoc(t_parser_var *var)
{
	int		rec_sig;
	t_data	*data;
	t_file	*file;

	data = var->data;
	rec_sig = 1;
	while (data)
	{
		data->last_hdc = 0;
		file = data->file;
		while (file)
		{
			if (file->type == 5 || file->type == 6)
				rec_sig = piping_forking(data, file, g_glob.envp);
			if (!rec_sig)
				return (false);
			file = file->next;
		}
		data = data->next;
	}
	return (true);
}

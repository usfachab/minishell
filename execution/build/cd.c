/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:44 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/09 16:21:28 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_store_pwd(t_parser_var *var)
{
	t_list	*tmp;

	tmp = var->env;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, "PWD=", 4))
		{
			free(tmp->content);
			free(tmp->next->content);
			tmp->content = ft_strjoin("PWD=", g_glob.pwd);
			tmp->next->content = ft_strjoin("OLDPWD=", g_glob.oldpwd);
		}
		tmp = tmp->next;
	}
}

int	is_not_dir(char *name)
{
	if (!name)
		return (1);
	struct stat	file_stat;

	if (!access(name, F_OK))
	{
		if (stat(name, &file_stat) == 0)
		{
			if (!S_ISDIR(file_stat.st_mode))
			{
				write(2, "minishell: ", 11);
				write(2, name, ft_strlen(name));
				write(2, ": not a directory\n", 19);
				g_glob.exit_status = 1;
				return (0);
			}
		}
	}
	return (1);
}

int	ft_cd_help_3(char *name)
{
	if (name[0] == '\0')
		return (0);
		if (!is_not_dir(name))
	{
		// if ()
		// 	exit(1);
		return (1);
	}
	if (access(name, F_OK)
		|| access(name, R_OK)
		|| access(name, X_OK))
	{
		write (2, "minishell: cd: ", 15);
		perror(name);
		g_glob.exit_status = 1;
		// if (1)
		// 	exit(1);
		return (1);
	}
	return (0);
}

int	ft_cd_help_1(t_list *tmp, int flag)
{
	while (tmp)
	{
		if (ft_strnstr(tmp->content, "HOME=", 5))
		{
			if (!is_not_dir(tmp->content + 5))
			{
				if (flag)
					exit(1);
				return (1);
			}
			if (ft_cd_help_3(tmp->content + 5))
			{
				if (flag)
					exit(1);
				return (1);
			}
			if (flag)
				exit (0);
			chdir(tmp->content + 5);
			if (g_glob.pwd)
				free(g_glob.pwd);
			g_glob.pwd = getcwd(NULL, 0);
			return (0);
		}
		tmp = tmp->next;
	}
	write (2, "cd: HOME not set\n", 17);
	g_glob.exit_status = 1;
	return (1);
}

int	ft_cd_help_2(t_data *data)
{
	if (!is_not_dir(data->cmd_args[1]))
	{
		// if ()
		// 	exit(1);
		return (1);
	}
	if (access(data->cmd_args[1], F_OK)
		|| access(data->cmd_args[1], R_OK)
		|| access(data->cmd_args[1], X_OK))
	{
		write (2, "minishell: cd: ", 15);
		perror(data->cmd_args[1]);
		g_glob.exit_status = 1;
		// if (1)
		// 	exit(1);
		return (1);
	}
	else if (data->cmd_args[1])
	{
		chdir(data->cmd_args[1]);
		if (g_glob.pwd)
			free(g_glob.pwd);
		g_glob.pwd = getcwd(NULL, 0);
		if (g_glob.pwd)
			g_glob.pwd_helper = g_glob.pwd;
	}
	return (0);
}

int	ft_cd(t_parser_var *var, t_data *data, int flag)
{
	t_list	*tmp;

	tmp = var->env;
	if (g_glob.oldpwd)
		free(g_glob.oldpwd);
	g_glob.oldpwd = getcwd(NULL, 0);
	if ((!data->cmd_args[1] || data->cmd_args[1][0] == '~'))
		return (ft_cd_help_1(tmp, flag));
	else
	{
		if (ft_cd_help_2(data))
			return (1);
		if (g_glob.pwd == NULL && g_glob.oldpwd == NULL)
		{
			write (2, "cd: error retrieving current directory: getcwd:", 47);
			write (2, " cannot access parent directories: ", 35);
			write (2, "No such file or directory\n", 26);
			g_glob.exit_status = 0;
			// if (flag)
			// 	exit (0);
			return (1);
		}
	}
	ft_store_pwd(var);
	return (0);
}
